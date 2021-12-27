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
/* BINDTOOL_HEADER_FILE(float_to_uchar.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(2c3f1d0b8cc9ab168f601b1e3a7222b6)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/float_to_uchar.h>
// pydoc.h is automatically generated in the build directory
#include <float_to_uchar_pydoc.h>

void bind_float_to_uchar(py::module& m)
{

    using float_to_uchar = ::gr::blocks::float_to_uchar;


    py::class_<float_to_uchar,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<float_to_uchar>>(m, "float_to_uchar", D(float_to_uchar))

        .def(py::init(&float_to_uchar::make), D(float_to_uchar, make))


        ;
}
