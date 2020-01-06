/* -*- c++ -*- */
/*
 * Copyright 2004-2011,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../audio_registry.h"
#include "oss_source.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/prefs.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/soundcard.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

namespace gr {
namespace audio {

source::sptr
oss_source_fcn(int sampling_rate, const std::string& device_name, bool ok_to_block)
{
    return source::sptr(new oss_source(sampling_rate, device_name, ok_to_block));
}

static std::string default_device_name()
{
    return prefs::singleton()->get_string(
        "audio_oss", "default_input_device", "/dev/dsp");
}

oss_source::oss_source(int sampling_rate, const std::string device_name, bool ok_to_block)
    : sync_block("audio_oss_source",
                 io_signature::make(0, 0, 0),
                 io_signature::make(1, 2, sizeof(float))),
      d_sampling_rate(sampling_rate),
      d_device_name(device_name.empty() ? default_device_name() : device_name),
      d_fd(-1),
      d_buffer(0),
      d_chunk_size(0)
{
    if ((d_fd = open(d_device_name.c_str(), O_RDONLY)) < 0) {
        GR_LOG_ERROR(d_logger,
                     boost::format("opening device %s: %s") % d_device_name %
                         strerror(errno));
        throw std::runtime_error("audio_oss_source");
    }

    double CHUNK_TIME =
        std::max(0.001, prefs::singleton()->get_double("audio_oss", "latency", 0.005));

    d_chunk_size = (int)(d_sampling_rate * CHUNK_TIME);
    set_output_multiple(d_chunk_size);

    d_buffer = new short[d_chunk_size * 2];

    int format = AFMT_S16_NE;
    int orig_format = format;
    if (ioctl(d_fd, SNDCTL_DSP_SETFMT, &format) < 0) {
        GR_LOG_ERROR(d_logger,
                     boost::format("%s ioctl failed %s") % d_device_name %
                         strerror(errno));
        throw std::runtime_error("audio_oss_source");
    }

    if (format != orig_format) {
        GR_LOG_ERROR(
            d_logger,
            boost::format("%s unable to support format %d. card requested %d instead.") %
                orig_format % format);
    }

    // set to stereo no matter what.  Some hardware only does stereo
    int channels = 2;
    if (ioctl(d_fd, SNDCTL_DSP_CHANNELS, &channels) < 0 || channels != 2) {
        GR_LOG_ERROR(d_logger,
                     boost::format("could not set STEREO mode: %s") % strerror(errno));
        throw std::runtime_error("audio_oss_source");
    }

    // set sampling freq
    int sf = sampling_rate;
    if (ioctl(d_fd, SNDCTL_DSP_SPEED, &sf) < 0) {
        GR_LOG_ERROR(d_logger,
                     boost::format("ERROR %s: invalid sampling_rate %d") % d_device_name %
                         sampling_rate);
        sampling_rate = 8000;
        if (ioctl(d_fd, SNDCTL_DSP_SPEED, &sf) < 0) {
            GR_LOG_ERROR(d_logger, "failed to set sampling_rate to 8000");
            throw std::runtime_error("audio_oss_source");
        }
    }
}

oss_source::~oss_source()
{
    close(d_fd);
    delete[] d_buffer;
}

int oss_source::work(int noutput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items)
{
    float* f0 = (float*)output_items[0];
    float* f1 = (float*)output_items[1]; // will be invalid if this is mono output

    const int shorts_per_item = 2; // L + R
    const int bytes_per_item = shorts_per_item * sizeof(short);

    // To minimize latency, never return more than CHUNK_TIME
    // worth of samples per call to work.

    noutput_items = std::min(noutput_items, d_chunk_size);

    int base = 0;
    int ntogo = noutput_items;

    while (ntogo > 0) {
        int nbytes = std::min(ntogo, d_chunk_size) * bytes_per_item;
        int result_nbytes = read(d_fd, d_buffer, nbytes);

        if (result_nbytes < 0) {
            GR_LOG_ERROR(d_logger,
                         boost::format("audio_oss_source: %s") % strerror(errno));
            return -1; // say we're done
        }

        if ((result_nbytes & (bytes_per_item - 1)) != 0) {
            GR_LOG_ERROR(d_logger, "internal error.");
            throw std::runtime_error("internal error");
        }

        int result_nitems = result_nbytes / bytes_per_item;

        // now unpack samples into output streams

        switch (output_items.size()) {
        case 1: // mono output
            for (int i = 0; i < result_nitems; i++) {
                f0[base + i] = d_buffer[2 * i + 0] * (1.0 / 32767);
            }
            break;

        case 2: // stereo output
            for (int i = 0; i < result_nitems; i++) {
                f0[base + i] = d_buffer[2 * i + 0] * (1.0 / 32767);
                f1[base + i] = d_buffer[2 * i + 1] * (1.0 / 32767);
            }
            break;

        default:
            assert(0);
        }

        ntogo -= result_nitems;
        base += result_nitems;
    }

    return noutput_items - ntogo;
}

} /* namespace audio */
} /* namespace gr */
