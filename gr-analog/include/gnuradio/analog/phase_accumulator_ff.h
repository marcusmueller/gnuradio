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


#ifndef INCLUDED_ANALOG_PHASE_ACCUMULATOR_FF_H
#define INCLUDED_ANALOG_PHASE_ACCUMULATOR_FF_H

#include <gnuradio/analog/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace analog {

    /*!
     * \brief accumulator, keeping the values in [-pi;+pi[
     * \ingroup analog
     *
     * \details
     * This block is a running sum of all samples flowing into it, but wraps the phase at +-pi
     *
     */
    class ANALOG_API phase_accumulator_ff : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<phase_accumulator_ff> sptr;
      virtual float phase() const = 0;

      virtual void set_phase(float p) = 0;

      /*!
       * \brief Return a shared_ptr to a new instance of analog::phase_accumulator_ff.
       *
       * To avoid accidental use of raw pointers, analog::phase_accumulator_ff's
       * constructor is in a private implementation
       * class. analog::phase_accumulator_ff::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace analog
} // namespace gr

#endif /* INCLUDED_ANALOG_PHASE_ACCUMULATOR_FF_H */

