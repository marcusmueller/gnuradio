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
/* BINDTOOL_HEADER_FILE(fmcomms2_sink.h)                                           */
/* BINDTOOL_HEADER_FILE_HASH(9fa4f916dcbaa8ebcad2903f1b9e958c)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/iio/fmcomms2_sink.h>
// pydoc.h is automatically generated in the build directory
#include <fmcomms2_sink_pydoc.h>


template <typename T>
void bind_fmcomms2_sink_template(py::module& m, const char* classname)
{

    using fmcomms2_sink = gr::iio::fmcomms2_sink<T>;


    py::class_<fmcomms2_sink,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<fmcomms2_sink>>(m, classname, D(fmcomms2_sink))


        .def(py::init(&fmcomms2_sink::make),
             py::arg("uri"),
             py::arg("ch_en"),
             py::arg("buffer_size"),
             py::arg("cyclic"),
             D(fmcomms2_sink, make))
        .def("set_bandwidth", &fmcomms2_sink::set_bandwidth, py::arg("longbandwidth"))
        .def("set_frequency", &fmcomms2_sink::set_frequency, py::arg("longfrequency"))
        .def("set_samplerate", &fmcomms2_sink::set_samplerate, py::arg("samplerate"))
        .def("set_attenuation",
             &fmcomms2_sink::set_attenuation,
             py::arg("chan"),
             py::arg("attenuation"))
        .def("set_filter_params",
             &fmcomms2_sink::set_filter_params,
             py::arg("filter_source"),
             py::arg("filter_filename") = "",
             py::arg("fpass") = 0.0,
             py::arg("fstop") = 0.0)
        .def("set_len_tag_key",
             &fmcomms2_sink::set_len_tag_key,
             py::arg("len_tag_key") = "");
}

void bind_fmcomms2_sink(py::module& m)
{
    bind_fmcomms2_sink_template<int16_t>(m, "fmcomms2_sink_s");
    bind_fmcomms2_sink_template<std::complex<int16_t>>(m, "fmcomms2_sink_sc16");
    bind_fmcomms2_sink_template<gr_complex>(m, "fmcomms2_sink_fc32");
}
