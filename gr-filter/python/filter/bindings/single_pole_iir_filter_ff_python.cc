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
/* BINDTOOL_HEADER_FILE(single_pole_iir_filter_ff.h) */
/* BINDTOOL_HEADER_FILE_HASH(7be0660478b5a45cdecbc65aabb2ecda)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/filter/single_pole_iir_filter_ff.h>
// pydoc.h is automatically generated in the build directory
#include <single_pole_iir_filter_ff_pydoc.h>

void bind_single_pole_iir_filter_ff(py::module& m)
{

    using single_pole_iir_filter_ff = ::gr::filter::single_pole_iir_filter_ff;


    py::class_<single_pole_iir_filter_ff,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<single_pole_iir_filter_ff>>(
        m, "single_pole_iir_filter_ff", D(single_pole_iir_filter_ff))

        .def(py::init(&single_pole_iir_filter_ff::make),
             py::arg("alpha"),
             py::arg("vlen") = 1,
             D(single_pole_iir_filter_ff, make))


        .def("set_taps",
             &single_pole_iir_filter_ff::set_taps,
             py::arg("alpha"),
             D(single_pole_iir_filter_ff, set_taps))

        ;
}
