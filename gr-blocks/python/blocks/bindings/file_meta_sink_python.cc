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
/* BINDTOOL_HEADER_FILE(file_meta_sink.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(ec543fc9f945cb8f426b6cf9216a0c2c)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/file_meta_sink.h>
// pydoc.h is automatically generated in the build directory
#include <file_meta_sink_pydoc.h>

void bind_file_meta_sink(py::module& m)
{
    using file_meta_sink = ::gr::blocks::file_meta_sink;

    py::enum_<gr::blocks::gr_file_types>(m, "gr_file_types")
        .value("GR_FILE_BYTE", gr::blocks::GR_FILE_BYTE)           // 0
        .value("GR_FILE_CHAR", gr::blocks::GR_FILE_CHAR)           // 0
        .value("GR_FILE_SHORT", gr::blocks::GR_FILE_SHORT)         // 1
        .value("GR_FILE_INT", gr::blocks::GR_FILE_INT)             // 2
        .value("GR_FILE_LONG", gr::blocks::GR_FILE_LONG)           // 3
        .value("GR_FILE_LONG_LONG", gr::blocks::GR_FILE_LONG_LONG) // 4
        .value("GR_FILE_FLOAT", gr::blocks::GR_FILE_FLOAT)         // 5
        .value("GR_FILE_DOUBLE", gr::blocks::GR_FILE_DOUBLE)       // 6
        .export_values();

    py::implicitly_convertible<int, gr::blocks::gr_file_types>();

    py::class_<file_meta_sink,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<file_meta_sink>>(m, "file_meta_sink", D(file_meta_sink))

        .def(py::init(&file_meta_sink::make),
             py::arg("itemsize"),
             py::arg("filename"),
             py::arg("samp_rate") = 1,
             py::arg("relative_rate") = 1,
             py::arg("type") = ::gr::blocks::gr_file_types::GR_FILE_FLOAT,
             py::arg("complex") = true,
             py::arg("max_segment_size") = 1000000,
             py::arg("extra_dict") = pmt::make_dict(),
             py::arg("detached_header") = false,
             D(file_meta_sink, make))


        .def("open", &file_meta_sink::open, py::arg("filename"), D(file_meta_sink, open))


        .def("close", &file_meta_sink::close, D(file_meta_sink, close))


        .def("do_update", &file_meta_sink::do_update, D(file_meta_sink, do_update))


        .def("set_unbuffered",
             &file_meta_sink::set_unbuffered,
             py::arg("unbuffered"),
             D(file_meta_sink, set_unbuffered))

        ;

    m.attr("METADATA_VERSION") = gr::blocks::METADATA_VERSION;
    m.attr("METADATA_HEADER_SIZE") = gr::blocks::METADATA_HEADER_SIZE;
}
