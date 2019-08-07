/* -*- c++ -*- */
/*
 * Copyright 2015 Free Software Foundation, Inc.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_DTV_DVBS2_INTERLEAVER_BB_IMPL_H
#define INCLUDED_DTV_DVBS2_INTERLEAVER_BB_IMPL_H

#include "../dvb/dvb_defines.h"

#include <gnuradio/dtv/dvbs2_interleaver_bb.h>

namespace gr {
namespace dtv {

class dvbs2_interleaver_bb_impl : public dvbs2_interleaver_bb
{
private:
    int frame_size;
    int signal_constellation;
    int code_rate;
    int mod;
    int packed_items;
    int rowaddr0;
    int rowaddr1;
    int rowaddr2;
    int rowaddr3;
    int rowaddr4;
    int rowaddr5;
    int rowaddr6;
    int rowaddr7;

public:
    dvbs2_interleaver_bb_impl(dvb_framesize_t framesize,
                              dvb_code_rate_t rate,
                              dvb_constellation_t constellation);
    ~dvbs2_interleaver_bb_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace dtv
} // namespace gr

#endif /* INCLUDED_DTV_DVBS2_INTERLEAVER_BB_IMPL_H */
