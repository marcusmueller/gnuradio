/* -*- c++ -*- */
/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef NETWORK_UDPHEADERTYPES_H_
#define NETWORK_UDPHEADERTYPES_H_

enum class udp_headertype : int {
    NONE = 0,
    SEQNUM = 1,
    SEQPLUSSIZE = 2,
    // 3 and 4 were defined but have been removed.  ATA kept as 5 for backward
    // compatibility.
    OLDATA = 5
};

#endif /* NETWORK_UDPHEADERTYPES_H_ */
