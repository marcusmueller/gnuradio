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
#include <config.h>
#endif

#include <qa_message_actions.h>
#include <gnuradio/basic_block.h>
#include <gnuradio/hier_block2.h>
#include <cppunit/TestAssert.h>
#include <gnuradio/random.h>

int g_state = 0;
void
qa_message_actions::modify_state(int state)
{
  g_state += state;
}

void testf(long state) {
  g_state += state;
}
void
qa_message_actions::test0()
{
  g_state = 0;
  gr::hier_block2_sptr dut(gr::make_hier_block2("dummy", gr::io_signature::make(0,0,0), gr::io_signature::make(0,0,0)));
  CPPUNIT_ASSERT(dut);
  boost::function<void(long)> actionfunctor = boost::bind(&qa_message_actions::modify_state, this, _1);
  boost::function<long(pmt::pmt_t)> convfunctor = boost::bind(pmt::to_long, _1);
  dut->register_msg_action(pmt::mp("test"), convfunctor, actionfunctor);
  dut->register_msg_action(pmt::mp("test"), convfunctor, testf);
  dut->register_msg_action(pmt::mp("test"), pmt::to_long, actionfunctor);
  dut->register_msg_action(pmt::mp("test"), pmt::to_long, testf);
  CPPUNIT_ASSERT_EQUAL(g_state, 0);
  dut->trigger_actions(pmt::mp("test"), pmt::from_long(1l));
  CPPUNIT_ASSERT_EQUAL(g_state, 4);
  dut->process_action_msg(pmt::cons(pmt::mp("test"), pmt::from_long(13l)));
  CPPUNIT_ASSERT_EQUAL(g_state, 4 + 4 * 13);
}

