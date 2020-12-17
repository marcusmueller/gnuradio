/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(pwr_squelch_ff.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(e1ff64fcbc54b37e480c87c78a898df0)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/analog/pwr_squelch_ff.h>
// pydoc.h is automatically generated in the build directory
#include <pwr_squelch_ff_pydoc.h>

void bind_pwr_squelch_ff(py::module& m)
{

    using pwr_squelch_ff = ::gr::analog::pwr_squelch_ff;


    py::class_<pwr_squelch_ff,
               gr::analog::squelch_base_ff,
               std::shared_ptr<pwr_squelch_ff>>(m, "pwr_squelch_ff", D(pwr_squelch_ff))

        .def(py::init(&pwr_squelch_ff::make),
             py::arg("db"),
             py::arg("alpha") = 1.0E-4,
             py::arg("ramp") = 0,
             py::arg("gate") = false,
             D(pwr_squelch_ff, make))


        .def("squelch_range",
             &pwr_squelch_ff::squelch_range,
             D(pwr_squelch_ff, squelch_range))


        .def("threshold", &pwr_squelch_ff::threshold, D(pwr_squelch_ff, threshold))


        .def("set_threshold",
             &pwr_squelch_ff::set_threshold,
             py::arg("db"),
             D(pwr_squelch_ff, set_threshold))


        .def("set_alpha",
             &pwr_squelch_ff::set_alpha,
             py::arg("alpha"),
             D(pwr_squelch_ff, set_alpha))


        .def("ramp", &pwr_squelch_ff::ramp, D(pwr_squelch_ff, ramp))


        .def("set_ramp",
             &pwr_squelch_ff::set_ramp,
             py::arg("ramp"),
             D(pwr_squelch_ff, set_ramp))


        .def("gate", &pwr_squelch_ff::gate, D(pwr_squelch_ff, gate))


        .def("set_gate",
             &pwr_squelch_ff::set_gate,
             py::arg("gate"),
             D(pwr_squelch_ff, set_gate))


        .def("unmuted", &pwr_squelch_ff::unmuted, D(pwr_squelch_ff, unmuted))

        ;
}
