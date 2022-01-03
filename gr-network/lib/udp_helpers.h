/* -*- c++ -*- */
/*
 * Copyright 2020 Free Software Foundation, Inc.
 * Copyright 2022 Marcus Müller
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#pragma once
namespace gr::network::udp {
static constexpr unsigned int MAX_PAYLOAD_SIZE_SMALL = 2000;
static constexpr unsigned int MAX_PAYLOAD_SIZE_MEDIUM = 5000;
static constexpr unsigned int PAYLOADS_SMALL_PER_BUFFER = 4000;
static constexpr unsigned int PAYLOADS_MEDIUM_PER_BUFFER = 2000;
static constexpr unsigned int PAYLOADS_LARGE_PER_BUFFER = 1500;
inline constexpr size_t circbuffer_size(uint16_t payload_size)
{
    // Let's keep the circular buffer from getting too big
    if (payload_size < MAX_PAYLOAD_SIZE_SMALL) {
        return payload_size * PAYLOADS_SMALL_PER_BUFFER;
    }
    if (payload_size < MAX_PAYLOAD_SIZE_MEDIUM) {
        return payload_size * PAYLOADS_MEDIUM_PER_BUFFER;
    }
    return payload_size * PAYLOADS_LARGE_PER_BUFFER;
}
} // namespace gr::network::udp
