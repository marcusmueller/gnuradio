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
/* BINDTOOL_HEADER_FILE(tpc_decoder.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(1fa6e3824d8662a40e410e5151c18441)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/fec/tpc_decoder.h>
// pydoc.h is automatically generated in the build directory
#include <tpc_decoder_pydoc.h>

void bind_tpc_decoder(py::module& m)
{

    using tpc_decoder = ::gr::fec::tpc_decoder;


    py::class_<tpc_decoder, gr::fec::generic_decoder, std::shared_ptr<tpc_decoder>>(
        m, "tpc_decoder", D(tpc_decoder))

        .def_static("make",
                    &tpc_decoder::make,
                    py::arg("row_poly"),
                    py::arg("col_poly"),
                    py::arg("krow"),
                    py::arg("kcol"),
                    py::arg("bval"),
                    py::arg("qval"),
                    py::arg("max_iter"),
                    py::arg("decoder_type"),
                    D(tpc_decoder, make))


        .def("rate", &tpc_decoder::rate, D(tpc_decoder, rate))


        .def("set_frame_size",
             &tpc_decoder::set_frame_size,
             py::arg("frame_size"),
             D(tpc_decoder, set_frame_size))

        ;
}
