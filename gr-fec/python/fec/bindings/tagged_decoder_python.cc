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
/* BINDTOOL_HEADER_FILE(tagged_decoder.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(c25f5bdfd9a61a4716599de4da1e731e)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/fec/tagged_decoder.h>
// pydoc.h is automatically generated in the build directory
#include <tagged_decoder_pydoc.h>

void bind_tagged_decoder(py::module& m)
{

    using tagged_decoder = ::gr::fec::tagged_decoder;


    py::class_<tagged_decoder,
               gr::tagged_stream_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<tagged_decoder>>(m, "tagged_decoder", D(tagged_decoder))

        .def(py::init(&tagged_decoder::make),
             py::arg("my_decoder"),
             py::arg("input_item_size"),
             py::arg("output_item_size"),
             py::arg("lengthtagname") = "packet_len",
             py::arg("mtu") = 1500,
             D(tagged_decoder, make))


        .def("work",
             &tagged_decoder::work,
             py::arg("noutput_items"),
             py::arg("ninput_items"),
             py::arg("input_items"),
             py::arg("output_items"),
             D(tagged_decoder, work))


        .def("calculate_output_stream_length",
             &tagged_decoder::calculate_output_stream_length,
             py::arg("ninput_items"),
             D(tagged_decoder, calculate_output_stream_length))

        ;
}
