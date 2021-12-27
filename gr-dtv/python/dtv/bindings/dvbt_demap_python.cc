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
/* BINDTOOL_GEN_AUTOMATIC(1)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(dvbt_demap.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(7f5868da5e6f3aadd3910d341144be8d)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/dtv/dvbt_demap.h>
// pydoc.h is automatically generated in the build directory
#include <dvbt_demap_pydoc.h>

void bind_dvbt_demap(py::module& m)
{

    using dvbt_demap = ::gr::dtv::dvbt_demap;


    py::class_<dvbt_demap, gr::block, gr::basic_block, std::shared_ptr<dvbt_demap>>(
        m, "dvbt_demap", D(dvbt_demap))

        .def(py::init(&dvbt_demap::make),
             py::arg("nsize"),
             py::arg("constellation"),
             py::arg("hierarchy"),
             py::arg("transmission"),
             py::arg("gain"),
             D(dvbt_demap, make))


        ;
}
