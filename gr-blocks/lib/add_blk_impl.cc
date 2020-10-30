/* -*- c++ -*- */
/*
 * Copyright 2004,2009,2010,2012,2018 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "add_blk_impl.h"
#include <gnuradio/io_signature.h>
#include <volk/volk.h>

namespace gr {
namespace blocks {

// Smart Pointer wrapper for all types
template <class T>
typename add_blk<T>::sptr add_blk<T>::make(size_t vlen)
{
    return gnuradio::make_block_sptr<add_blk_impl<T>>(vlen);
}


// Float implementation
template <>
add_blk_impl<float>::add_blk_impl(size_t vlen)
    : sync_block("add_ff",
                 io_signature::make(1, -1, sizeof(float) * vlen),
                 io_signature::make(1, 1, sizeof(float) * vlen)),
      d_vlen(vlen)
{
    const int alignment_multiple = volk_get_alignment() / sizeof(float);
    set_alignment(std::max(1, alignment_multiple));
}

template <>
int add_blk_impl<float>::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    float* out = static_cast<float*>(output_items[0]);
    int noi = d_vlen * noutput_items;

    // strange single-input add case
    if (input_items.size() == 1) {
        memcpy(out, input_items[0], noi * sizeof(float));
        return noutput_items;
    }

    // for two inputs, add up the two inputs into the output
    volk_32f_x2_add_32f(out,
                        static_cast<const float*>(input_items[0]),
                        static_cast<const float*>(input_items[1]),
                        noi);

    // for more inputs, add the rest on top
    for (size_t i = 2; i < input_items.size(); i++) {
        volk_32f_x2_add_32f(out, out, static_cast<const float*>(input_items[i]), noi);
    }
    return noutput_items;
}


// Complex implementation
template <>
add_blk_impl<gr_complex>::add_blk_impl(size_t vlen)
    : sync_block("add_cc",
                 io_signature::make(1, -1, sizeof(gr_complex) * vlen),
                 io_signature::make(1, 1, sizeof(gr_complex) * vlen)),
      d_vlen(vlen)
{
    // addition is done on floats, so no need to complex-align
    const int alignment_multiple = volk_get_alignment() / sizeof(gr_complex);
    set_alignment(std::max(1, alignment_multiple));
}

template <>
int add_blk_impl<gr_complex>::work(int noutput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    float* out = static_cast<float*>(output_items[0]);
    int noi = d_vlen * noutput_items * 2; // attention: number of floats!

    // strange single-input add case
    if (input_items.size() == 1) {
        memcpy(out, input_items[0], noi * sizeof(float));
        return noutput_items;
    }

    // for two inputs, add up the two inputs into the output
    volk_32f_x2_add_32f(out,
                        static_cast<const float*>(input_items[0]),
                        static_cast<const float*>(input_items[1]),
                        noi);

    // for more inputs, add the rest on top
    for (size_t i = 2; i < input_items.size(); i++) {
        volk_32f_x2_add_32f(out, out, static_cast<const float*>(input_items[i]), noi);
    }
    return noutput_items;
}


// Generic implementation
template <class T>
add_blk_impl<T>::add_blk_impl(size_t vlen)
    : sync_block("add_blk",
                 io_signature::make(1, -1, sizeof(T) * vlen),
                 io_signature::make(1, 1, sizeof(T) * vlen)),
      d_vlen(vlen)
{
}

template <class T>
int add_blk_impl<T>::work(int noutput_items,
                          gr_vector_const_void_star& input_items,
                          gr_vector_void_star& output_items)
{
    T* optr = (T*)output_items[0];

    int ninputs = input_items.size();

    for (size_t i = 0; i < noutput_items * d_vlen; i++) {
        T acc = ((T*)input_items[0])[i];
        for (int j = 1; j < ninputs; j++)
            acc += ((T*)input_items[j])[i];

        *optr++ = (T)acc;
    }

    return noutput_items;
}

template class add_blk<std::int16_t>;
template class add_blk<std::int32_t>;
template class add_blk<gr_complex>;
template class add_blk<float>;
} /* namespace blocks */
} /* namespace gr */
