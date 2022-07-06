/*
 * Copyright 2020 Free Software Foundation, Inc.
 * Copyright 2022 Marcus Müller
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
/* BINDTOOL_HEADER_FILE(noise_source.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(65566b2708852e8118e54a18aed0a292)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/analog/noise_source.h>

template <typename T>
void bind_noise_source_template(py::module& m, const char* classname)
{
    using noise_source = gr::analog::noise_source<T>;

    py::class_<noise_source,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<noise_source>>(m, classname)
        .def(py::init([](gr::analog::noise_type_t type, float ampl, int64_t seed) {
                 return gr::analog::noise_source<T>::make(type, ampl, seed);
             }),
             py::arg("type"),
             py::arg("ampl"),
             py::arg("seed").noconvert(true) = 0)
        .def(py::init([](gr::analog::noise_type_t type, float ampl, uint64_t seed) {
                 return gr::analog::noise_source<T>::make(type, ampl, seed);
             }),
             py::arg("type"),
             py::arg("ampl"),
             py::arg("seed").noconvert(true) = 0)

        .def("set_type", &noise_source::set_type, py::arg("type"))
        .def("set_amplitude", &noise_source::set_amplitude, py::arg("ampl"))

        .def("type", &noise_source::type)
        .def("amplitude", &noise_source::amplitude);
}

void bind_noise_source(py::module& m)
{
    bind_noise_source_template<std::int16_t>(m, "noise_source_s");
    bind_noise_source_template<std::int32_t>(m, "noise_source_i");
    bind_noise_source_template<float>(m, "noise_source_f");
    bind_noise_source_template<gr_complex>(m, "noise_source_c");
}
