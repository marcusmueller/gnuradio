/* -*- c++ -*- */
/* 
 * Copyright 2015 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "phase_accumulator_ff_impl.h"
#include <cmath>

namespace gr {
  namespace analog {

    phase_accumulator_ff::sptr
    phase_accumulator_ff::make()
    {
      return gnuradio::get_initial_sptr
        (new phase_accumulator_ff_impl());
    }

    /*
     * The private constructor
     */
    phase_accumulator_ff_impl::phase_accumulator_ff_impl()
      : gr::sync_block("phase_accumulator_ff",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float))),
      d_phase(0)
    {
    }

    /*
     * Our virtual destructor.
     */
    phase_accumulator_ff_impl::~phase_accumulator_ff_impl()
    {
    }

    int
    phase_accumulator_ff_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
#define F_PI ((float)(M_PI))
        const float *in = (const float *) input_items[0];
        float *out = (float *) output_items[0];
        for(int counter = 0; counter < noutput_items; ++counter)
        {
            out[counter] = d_phase = std::fmod(d_phase + in[counter]  + F_PI, 2.0f * F_PI) - F_PI;
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace analog */
} /* namespace gr */

