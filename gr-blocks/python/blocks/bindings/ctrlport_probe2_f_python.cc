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
/* BINDTOOL_HEADER_FILE(ctrlport_probe2_f.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(22dbbadd9a269ca56a97b122cfa97cf6)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/ctrlport_probe2_f.h>
// pydoc.h is automatically generated in the build directory
#include <ctrlport_probe2_f_pydoc.h>

void bind_ctrlport_probe2_f(py::module& m)
{

    using ctrlport_probe2_f = ::gr::blocks::ctrlport_probe2_f;


    py::class_<ctrlport_probe2_f,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<ctrlport_probe2_f>>(
        m, "ctrlport_probe2_f", D(ctrlport_probe2_f))

        .def(py::init(&ctrlport_probe2_f::make),
             py::arg("id"),
             py::arg("desc"),
             py::arg("len"),
             py::arg("disp_mask"),
             D(ctrlport_probe2_f, make))


        .def("get", &ctrlport_probe2_f::get, D(ctrlport_probe2_f, get))


        .def("set_length",
             &ctrlport_probe2_f::set_length,
             py::arg("len"),
             D(ctrlport_probe2_f, set_length))

        ;
}
