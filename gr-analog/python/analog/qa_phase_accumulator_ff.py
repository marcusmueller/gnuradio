#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2015 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
#import analog_swig as analog
from gnuradio import analog
import numpy
import math

class qa_phase_accumulator_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()
        self.sensitivity = 1.0/(1e4*math.pi)

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        """
        checks this against the frequency modulator
        """
        data_source = blocks.vector_source_f(tuple([i/1000.0 for i in xrange(1024)]))

        reference = analog.frequency_modulator_fc(self.sensitivity)
        ref_sink = blocks.vector_sink_c()
        self.tb.connect(data_source, reference)
        self.tb.connect(reference, ref_sink)

        dut = analog.phase_accumulator_ff()
        mult = blocks.multiply_const_ff(self.sensitivity)
        phasemod = analog.phase_modulator_fc(1.0)
        data_sink = blocks.vector_sink_c()
        phase_sink = blocks.vector_sink_f()
        self.tb.connect(data_source, mult)
        self.tb.connect(mult, dut)
        self.tb.connect(dut, phasemod)
        self.tb.connect(dut, phase_sink)
        self.tb.connect(phasemod,  data_sink)

        # set up fg
        self.tb.run ()
        result_data = data_sink.data()
        ref_data    = ref_sink.data()
        self.assertComplexTuplesAlmostEqual(result_data, ref_data, 5)


if __name__ == '__main__':
    gr_unittest.run(qa_phase_accumulator_ff, "qa_phase_accumulator_ff.xml")
