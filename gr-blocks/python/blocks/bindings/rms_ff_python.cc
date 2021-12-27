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
/* BINDTOOL_HEADER_FILE(rms_ff.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(4054a91408ad6548d59b40df57a50ca5)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/rms_ff.h>
// pydoc.h is automatically generated in the build directory
#include <rms_ff_pydoc.h>

void bind_rms_ff(py::module& m)
{

    using rms_ff = ::gr::blocks::rms_ff;


    py::class_<rms_ff,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<rms_ff>>(m, "rms_ff", D(rms_ff))

        .def(py::init(&rms_ff::make), py::arg("alpha") = 1.0E-4, D(rms_ff, make))


        .def("set_alpha", &rms_ff::set_alpha, py::arg("alpha"), D(rms_ff, set_alpha))

        ;
}
