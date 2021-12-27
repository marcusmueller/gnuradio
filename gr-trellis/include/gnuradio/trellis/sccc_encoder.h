/* -*- c++ -*- */
/*
 * Copyright 2004,2012,2018 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef SCCC_ENCODER_H
#define SCCC_ENCODER_H

#include <gnuradio/sync_block.h>
#include <gnuradio/trellis/api.h>
#include <gnuradio/trellis/fsm.h>
#include <gnuradio/trellis/interleaver.h>
#include <vector>

namespace gr {
namespace trellis {

/*!
 * \brief SCCC encoder.
 * \ingroup trellis_coding_blk
 */
template <class IN_T, class OUT_T>
class TRELLIS_API sccc_encoder : virtual public sync_block
{
public:
    using sptr = std::shared_ptr<sccc_encoder<IN_T, OUT_T>>;

    static sptr make(const fsm& FSMo,
                     int STo,
                     const fsm& FSMi,
                     int STi,
                     const interleaver& INTERLEAVER,
                     int blocklength);

    virtual fsm FSMo() const = 0;
    virtual int STo() const = 0;
    virtual fsm FSMi() const = 0;
    virtual int STi() const = 0;
    virtual interleaver INTERLEAVER() const = 0;
    virtual int blocklength() const = 0;
};
using sccc_encoder_bb = sccc_encoder<std::uint8_t, std::uint8_t>;
using sccc_encoder_bs = sccc_encoder<std::uint8_t, std::int16_t>;
using sccc_encoder_bi = sccc_encoder<std::uint8_t, std::int32_t>;
using sccc_encoder_ss = sccc_encoder<std::int16_t, std::int16_t>;
using sccc_encoder_si = sccc_encoder<std::uint8_t, std::int32_t>;
using sccc_encoder_ii = sccc_encoder<std::int32_t, std::int32_t>;

} /* namespace trellis */
} /* namespace gr */

#endif /* SCCC_ENCODER_H */
