/* -*- c++ -*- */
/*
 * Copyright 2013,2014 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio.
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

#ifndef INCLUDED_ZEROMQ_PULL_SOURCE_IMPL_H
#define INCLUDED_ZEROMQ_PULL_SOURCE_IMPL_H

#include <gnuradio/zeromq/pull_source.h>
#include <zmq.hpp>

#include "base_impl.h"

namespace gr {
namespace zeromq {

class pull_source_impl : public pull_source, public base_source_impl
{
public:
    pull_source_impl(size_t itemsize,
                     size_t vlen,
                     char* address,
                     int timeout,
                     bool pass_tags,
                     int hwm);

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
    std::string last_endpoint() override { return base_source_impl::last_endpoint(); }
};

} // namespace zeromq
} // namespace gr

#endif /* INCLUDED_ZEROMQ_PULL_SOURCE_IMPL_H */
