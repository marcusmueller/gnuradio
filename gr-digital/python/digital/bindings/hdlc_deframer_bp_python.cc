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
/* BINDTOOL_HEADER_FILE(hdlc_deframer_bp.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(9aa6cb661a072da0b8165fb38c991677)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/digital/hdlc_deframer_bp.h>
// pydoc.h is automatically generated in the build directory
#include <hdlc_deframer_bp_pydoc.h>

void bind_hdlc_deframer_bp(py::module& m)
{

    using hdlc_deframer_bp = ::gr::digital::hdlc_deframer_bp;


    py::class_<hdlc_deframer_bp,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<hdlc_deframer_bp>>(
        m, "hdlc_deframer_bp", D(hdlc_deframer_bp))

        .def(py::init(&hdlc_deframer_bp::make),
             py::arg("length_min"),
             py::arg("length_max"),
             D(hdlc_deframer_bp, make))


        ;
}
