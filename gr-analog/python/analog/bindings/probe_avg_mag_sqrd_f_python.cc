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
/* BINDTOOL_HEADER_FILE(probe_avg_mag_sqrd_f.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(95ed5fead647105d787a3cae04619d6f)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/analog/probe_avg_mag_sqrd_f.h>
// pydoc.h is automatically generated in the build directory
#include <probe_avg_mag_sqrd_f_pydoc.h>

void bind_probe_avg_mag_sqrd_f(py::module& m)
{

    using probe_avg_mag_sqrd_f = ::gr::analog::probe_avg_mag_sqrd_f;


    py::class_<probe_avg_mag_sqrd_f,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<probe_avg_mag_sqrd_f>>(
        m, "probe_avg_mag_sqrd_f", D(probe_avg_mag_sqrd_f))

        .def(py::init(&probe_avg_mag_sqrd_f::make),
             py::arg("threshold_db"),
             py::arg("alpha") = 1.0E-4,
             D(probe_avg_mag_sqrd_f, make))


        .def("unmuted", &probe_avg_mag_sqrd_f::unmuted, D(probe_avg_mag_sqrd_f, unmuted))


        .def("level", &probe_avg_mag_sqrd_f::level, D(probe_avg_mag_sqrd_f, level))


        .def("threshold",
             &probe_avg_mag_sqrd_f::threshold,
             D(probe_avg_mag_sqrd_f, threshold))


        .def("set_alpha",
             &probe_avg_mag_sqrd_f::set_alpha,
             py::arg("alpha"),
             D(probe_avg_mag_sqrd_f, set_alpha))


        .def("set_threshold",
             &probe_avg_mag_sqrd_f::set_threshold,
             py::arg("decibels"),
             D(probe_avg_mag_sqrd_f, set_threshold))


        .def("reset", &probe_avg_mag_sqrd_f::reset, D(probe_avg_mag_sqrd_f, reset))

        ;
}
