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
/* BINDTOOL_HEADER_FILE(rms_cf.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(33b3dee74cef107ce88a3a33e7e0955e)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/rms_cf.h>
// pydoc.h is automatically generated in the build directory
#include <rms_cf_pydoc.h>

void bind_rms_cf(py::module& m)
{

    using rms_cf = ::gr::blocks::rms_cf;


    py::class_<rms_cf,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<rms_cf>>(m, "rms_cf", D(rms_cf))

        .def(py::init(&rms_cf::make), py::arg("alpha") = 1.0E-4, D(rms_cf, make))


        .def("set_alpha", &rms_cf::set_alpha, py::arg("alpha"), D(rms_cf, set_alpha))

        ;
}
