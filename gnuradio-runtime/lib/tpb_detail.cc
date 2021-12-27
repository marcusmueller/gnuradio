/* -*- c++ -*- */
/*
 * Copyright 2008,2009,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gnuradio/block.h>
#include <gnuradio/block_detail.h>
#include <gnuradio/buffer.h>
#include <gnuradio/buffer_reader.h>
#include <gnuradio/tpb_detail.h>

namespace gr {

/*
 * We assume that no worker threads are ever running when the graph
 * structure is being manipulated, thus it's safe for us to poke
 * around in our neighbors w/o holding any locks.
 */
void tpb_detail::notify_upstream(block_detail* d)
{
    // For each of our inputs, tell the guy upstream that we've
    // consumed some input, and that he most likely has more output
    // buffer space available.

    for (auto& i : d->d_input) {
        // Can you say, "pointer chasing?"
        i->buffer()->link()->detail()->d_tpb.set_output_changed();
    }
}

void tpb_detail::notify_downstream(block_detail* d)
{
    // For each of our outputs, tell the guys downstream that they
    // have new input available.

    for (auto buf : d->d_output) {
        for (size_t j = 0, k = buf->nreaders(); j < k; j++)
            buf->reader(j)->link()->detail()->d_tpb.set_input_changed();
    }
}

void tpb_detail::notify_neighbors(block_detail* d)
{
    notify_downstream(d);
    notify_upstream(d);
}

} /* namespace gr */
