/* -*- c++ -*- */
/*
 * Copyright 2006,2012 Free Software Foundation, Inc.
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

#ifndef INCLUDED_ANALOG_PWR_SQUELCH_CC_IMPL_H
#define INCLUDED_ANALOG_PWR_SQUELCH_CC_IMPL_H

#include "squelch_base_cc_impl.h"
#include <gnuradio/analog/pwr_squelch_cc.h>
#include <gnuradio/filter/single_pole_iir.h>
#include <cmath>

namespace gr {
namespace analog {

class ANALOG_API pwr_squelch_cc_impl : public pwr_squelch_cc, squelch_base_cc_impl
{
private:
    double d_threshold;
    double d_pwr;
    filter::single_pole_iir<double, double, double> d_iir;

protected:
    void update_state(const gr_complex& in) override;
    bool mute() const override { return d_pwr < d_threshold; }

public:
    pwr_squelch_cc_impl(double db,
                        double alpha = 0.0001,
                        int ramp = 0,
                        bool gate = false);
    ~pwr_squelch_cc_impl() override;

    std::vector<float> squelch_range() const override;

    double threshold() const override { return 10 * log10(d_threshold); }
    void set_threshold(double db) override;
    void set_alpha(double alpha) override;

    int ramp() const override { return squelch_base_cc_impl::ramp(); }
    void set_ramp(int ramp) override { squelch_base_cc_impl::set_ramp(ramp); }
    bool gate() const override { return squelch_base_cc_impl::gate(); }
    void set_gate(bool gate) override { squelch_base_cc_impl::set_gate(gate); }
    bool unmuted() const override { return squelch_base_cc_impl::unmuted(); }

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override
    {
        return squelch_base_cc_impl::general_work(
            noutput_items, ninput_items, input_items, output_items);
    }
};

} /* namespace analog */
} /* namespace gr */

#endif /* INCLUDED_ANALOG_PWR_SQUELCH_CC_IMPL_H */
