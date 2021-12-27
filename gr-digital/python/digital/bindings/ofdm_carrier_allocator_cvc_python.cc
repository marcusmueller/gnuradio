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
/* BINDTOOL_HEADER_FILE(ofdm_carrier_allocator_cvc.h) */
/* BINDTOOL_HEADER_FILE_HASH(6699c7ccb58847a2f9ea243573f78715)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/digital/ofdm_carrier_allocator_cvc.h>
// pydoc.h is automatically generated in the build directory
#include <ofdm_carrier_allocator_cvc_pydoc.h>

void bind_ofdm_carrier_allocator_cvc(py::module& m)
{

    using ofdm_carrier_allocator_cvc = ::gr::digital::ofdm_carrier_allocator_cvc;


    py::class_<ofdm_carrier_allocator_cvc,
               gr::tagged_stream_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<ofdm_carrier_allocator_cvc>>(
        m, "ofdm_carrier_allocator_cvc", D(ofdm_carrier_allocator_cvc))

        .def(py::init(&ofdm_carrier_allocator_cvc::make),
             py::arg("fft_len"),
             py::arg("occupied_carriers"),
             py::arg("pilot_carriers"),
             py::arg("pilot_symbols"),
             py::arg("sync_words"),
             py::arg("len_tag_key") = "packet_len",
             py::arg("output_is_shifted") = true,
             D(ofdm_carrier_allocator_cvc, make))


        .def("len_tag_key",
             &ofdm_carrier_allocator_cvc::len_tag_key,
             D(ofdm_carrier_allocator_cvc, len_tag_key))


        .def("fft_len",
             &ofdm_carrier_allocator_cvc::fft_len,
             D(ofdm_carrier_allocator_cvc, fft_len))


        .def("occupied_carriers",
             &ofdm_carrier_allocator_cvc::occupied_carriers,
             D(ofdm_carrier_allocator_cvc, occupied_carriers))


        ;
}
