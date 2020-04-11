/* -*- c++ -*- */
/*
 * Copyright 2016-2019 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef INCLUDED_VOCODER_FREEDV_TX_SS_IMPL_H
#define INCLUDED_VOCODER_FREEDV_TX_SS_IMPL_H

#include <gnuradio/logger.h>
#include <gnuradio/vocoder/freedv_tx_ss.h>

extern "C" {
struct freedv_tx_callback_state {
    char tx_str[80];
    char* ptx_str;
    int calls;
};
char get_next_tx_char(void* callback_state);
void get_next_proto(void* callback_state, char* proto_bits);
void datarx(void* callback_state, unsigned char* packet, size_t size);
void datatx(void* callback_state, unsigned char* packet, size_t* size);
}

namespace gr {
namespace vocoder {

class freedv_tx_ss_impl : public freedv_tx_ss
{
private:
    gr::logger_ptr d_logger, d_debug_logger;
    struct freedv_tx_callback_state d_cb_state;
    struct freedv* d_freedv;
    std::string d_msg_text;
    int d_nom_modem_samples;
    int d_clip;
    int d_tx_bpf;

public:
    freedv_tx_ss_impl(freedv_api::freedv_modes mode,
                      const std::string txt_msg,
                      int interleave_frames);
    ~freedv_tx_ss_impl();

    void set_clip(bool val);
    void set_clip(int val);
    void set_tx_bpf(bool val);
    void set_tx_bpf(int val);

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} /* namespace vocoder */
} /* namespace gr */

#endif /* INCLUDED_VOCODER_FREEDV_TX_SS_IMPL_H */
