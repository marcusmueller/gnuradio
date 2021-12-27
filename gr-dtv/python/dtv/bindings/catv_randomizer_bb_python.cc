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
/* BINDTOOL_HEADER_FILE(catv_randomizer_bb.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(1708ad8e4d07aa67ece564e02c4b462c)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/dtv/catv_randomizer_bb.h>
// pydoc.h is automatically generated in the build directory
#include <catv_randomizer_bb_pydoc.h>

void bind_catv_randomizer_bb(py::module& m)
{

    using catv_randomizer_bb = ::gr::dtv::catv_randomizer_bb;


    py::class_<catv_randomizer_bb,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<catv_randomizer_bb>>(
        m, "catv_randomizer_bb", D(catv_randomizer_bb))

        .def(py::init(&catv_randomizer_bb::make),
             py::arg("constellation"),
             D(catv_randomizer_bb, make))


        ;
}
