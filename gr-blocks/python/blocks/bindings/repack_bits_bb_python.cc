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
/* BINDTOOL_HEADER_FILE(repack_bits_bb.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(0757a669c7dd01d390f73624d89fcfe2)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/repack_bits_bb.h>
// pydoc.h is automatically generated in the build directory
#include <repack_bits_bb_pydoc.h>

void bind_repack_bits_bb(py::module& m)
{

    using repack_bits_bb = ::gr::blocks::repack_bits_bb;


    py::class_<repack_bits_bb,
               gr::tagged_stream_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<repack_bits_bb>>(m, "repack_bits_bb", D(repack_bits_bb))

        .def(py::init(&repack_bits_bb::make),
             py::arg("k"),
             py::arg("l") = 8,
             py::arg("tsb_tag_key") = "",
             py::arg("align_output") = false,
             py::arg("endianness") = ::gr::endianness_t::GR_LSB_FIRST,
             D(repack_bits_bb, make))


        .def("set_k_and_l",
             &repack_bits_bb::set_k_and_l,
             py::arg("k"),
             py::arg("l"),
             D(repack_bits_bb, set_k_and_l))

        ;
}
