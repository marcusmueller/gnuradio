/* -*- c++ -*- */
/*
 * Copyright 2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_CHANNELS_CHANNEL_MODEL_IMPL_H
#define INCLUDED_CHANNELS_CHANNEL_MODEL_IMPL_H

#include "flat_fader_impl.h"
#include <gnuradio/channels/fading_model.h>
#include <gnuradio/sync_block.h>

//#include <iostream>
#include <boost/format.hpp>
#include <boost/random.hpp>

#include "sincostable.h"
#include <gnuradio/fxpt.h>

namespace gr {
namespace channels {

class CHANNELS_API fading_model_impl : public fading_model
{
private:
    gr::channels::flat_fader_impl d_fader;

public:
    fading_model_impl(unsigned int N, float fDTs, bool LOS, float K, int seed);
    ~fading_model_impl() override;
    void setup_rpc() override;
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

    float fDTs() override { return d_fader.d_fDTs; }
    float K() override { return d_fader.d_K; }
    float step() override { return d_fader.d_step; }

    void set_fDTs(float fDTs) override
    {
        d_fader.d_fDTs = fDTs;
        d_fader.d_step = powf(0.00125 * fDTs, 1.1);
    }
    void set_K(float K) override
    {
        d_fader.d_K = K;
        d_fader.scale_los = sqrtf(d_fader.d_K) / sqrtf(d_fader.d_K + 1);
        d_fader.scale_nlos = (1 / sqrtf(d_fader.d_K + 1));
    }
    void set_step(float step) override { d_fader.d_step = step; }
};

} /* namespace channels */
} /* namespace gr */

#endif /* INCLUDED_CHANNELS_CHANNEL_MODEL_IMPL_H */
