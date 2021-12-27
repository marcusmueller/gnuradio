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
/* BINDTOOL_HEADER_FILE(tag_debug.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(5eb97d800ff39d0236da9ef8a0ea6328)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/tag_debug.h>
// pydoc.h is automatically generated in the build directory
#include <tag_debug_pydoc.h>

void bind_tag_debug(py::module& m)
{

    using tag_debug = ::gr::blocks::tag_debug;


    py::class_<tag_debug,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<tag_debug>>(m, "tag_debug", D(tag_debug))

        .def(py::init(&tag_debug::make),
             py::arg("sizeof_stream_item"),
             py::arg("name"),
             py::arg("key_filter") = "",
             D(tag_debug, make))


        .def("current_tags", &tag_debug::current_tags, D(tag_debug, current_tags))


        .def("num_tags", &tag_debug::num_tags, D(tag_debug, num_tags))


        .def("set_display",
             &tag_debug::set_display,
             py::arg("d"),
             D(tag_debug, set_display))


        .def("set_save_all",
             &tag_debug::set_save_all,
             py::arg("s"),
             D(tag_debug, set_save_all))


        .def("set_key_filter",
             &tag_debug::set_key_filter,
             py::arg("key_filter"),
             D(tag_debug, set_key_filter))


        .def("key_filter", &tag_debug::key_filter, D(tag_debug, key_filter))

        ;
}
