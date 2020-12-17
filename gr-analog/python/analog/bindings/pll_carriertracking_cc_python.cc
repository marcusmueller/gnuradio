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
/* BINDTOOL_HEADER_FILE(pll_carriertracking_cc.h) */
/* BINDTOOL_HEADER_FILE_HASH(578b0d642e583a358c5866cb1b663756)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/analog/pll_carriertracking_cc.h>
// pydoc.h is automatically generated in the build directory
#include <pll_carriertracking_cc_pydoc.h>

void bind_pll_carriertracking_cc(py::module& m)
{

    using pll_carriertracking_cc = ::gr::analog::pll_carriertracking_cc;


    py::class_<pll_carriertracking_cc,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<pll_carriertracking_cc>>(
        m, "pll_carriertracking_cc", D(pll_carriertracking_cc))

        .def(py::init(&pll_carriertracking_cc::make),
             py::arg("loop_bw"),
             py::arg("max_freq"),
             py::arg("min_freq"),
             D(pll_carriertracking_cc, make))


        .def("lock_detector",
             &pll_carriertracking_cc::lock_detector,
             D(pll_carriertracking_cc, lock_detector))


        .def("squelch_enable",
             &pll_carriertracking_cc::squelch_enable,
             py::arg("arg0"),
             D(pll_carriertracking_cc, squelch_enable))


        .def("set_lock_threshold",
             &pll_carriertracking_cc::set_lock_threshold,
             py::arg("arg0"),
             D(pll_carriertracking_cc, set_lock_threshold))


        .def("set_loop_bandwidth",
             &pll_carriertracking_cc::set_loop_bandwidth,
             py::arg("bw"),
             D(pll_carriertracking_cc, set_loop_bandwidth))


        .def("set_damping_factor",
             &pll_carriertracking_cc::set_damping_factor,
             py::arg("df"),
             D(pll_carriertracking_cc, set_damping_factor))


        .def("set_alpha",
             &pll_carriertracking_cc::set_alpha,
             py::arg("alpha"),
             D(pll_carriertracking_cc, set_alpha))


        .def("set_beta",
             &pll_carriertracking_cc::set_beta,
             py::arg("beta"),
             D(pll_carriertracking_cc, set_beta))


        .def("set_frequency",
             &pll_carriertracking_cc::set_frequency,
             py::arg("freq"),
             D(pll_carriertracking_cc, set_frequency))


        .def("set_phase",
             &pll_carriertracking_cc::set_phase,
             py::arg("phase"),
             D(pll_carriertracking_cc, set_phase))


        .def("set_min_freq",
             &pll_carriertracking_cc::set_min_freq,
             py::arg("freq"),
             D(pll_carriertracking_cc, set_min_freq))


        .def("set_max_freq",
             &pll_carriertracking_cc::set_max_freq,
             py::arg("freq"),
             D(pll_carriertracking_cc, set_max_freq))


        .def("get_loop_bandwidth",
             &pll_carriertracking_cc::get_loop_bandwidth,
             D(pll_carriertracking_cc, get_loop_bandwidth))


        .def("get_damping_factor",
             &pll_carriertracking_cc::get_damping_factor,
             D(pll_carriertracking_cc, get_damping_factor))


        .def("get_alpha",
             &pll_carriertracking_cc::get_alpha,
             D(pll_carriertracking_cc, get_alpha))


        .def("get_beta",
             &pll_carriertracking_cc::get_beta,
             D(pll_carriertracking_cc, get_beta))


        .def("get_frequency",
             &pll_carriertracking_cc::get_frequency,
             D(pll_carriertracking_cc, get_frequency))


        .def("get_phase",
             &pll_carriertracking_cc::get_phase,
             D(pll_carriertracking_cc, get_phase))


        .def("get_min_freq",
             &pll_carriertracking_cc::get_min_freq,
             D(pll_carriertracking_cc, get_min_freq))


        .def("get_max_freq",
             &pll_carriertracking_cc::get_max_freq,
             D(pll_carriertracking_cc, get_max_freq))

        ;
}
