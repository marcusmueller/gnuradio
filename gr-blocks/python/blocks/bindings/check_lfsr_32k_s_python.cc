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
/* BINDTOOL_HEADER_FILE(check_lfsr_32k_s.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(5f1c85d468d083d30367c7e39b3f039c)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/check_lfsr_32k_s.h>
// pydoc.h is automatically generated in the build directory
#include <check_lfsr_32k_s_pydoc.h>

void bind_check_lfsr_32k_s(py::module& m)
{

    using check_lfsr_32k_s = ::gr::blocks::check_lfsr_32k_s;


    py::class_<check_lfsr_32k_s,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<check_lfsr_32k_s>>(
        m, "check_lfsr_32k_s", D(check_lfsr_32k_s))

        .def(py::init(&check_lfsr_32k_s::make), D(check_lfsr_32k_s, make))


        .def("ntotal", &check_lfsr_32k_s::ntotal, D(check_lfsr_32k_s, ntotal))


        .def("nright", &check_lfsr_32k_s::nright, D(check_lfsr_32k_s, nright))


        .def("runlength", &check_lfsr_32k_s::runlength, D(check_lfsr_32k_s, runlength))

        ;
}
