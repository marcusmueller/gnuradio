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
/* BINDTOOL_HEADER_FILE(wavelet_ff.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(1d7d68540ec237e02366a3de76c71f41)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/wavelet/wavelet_ff.h>
// pydoc.h is automatically generated in the build directory
#include <wavelet_ff_pydoc.h>

void bind_wavelet_ff(py::module& m)
{

    using wavelet_ff = ::gr::wavelet::wavelet_ff;


    py::class_<wavelet_ff,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<wavelet_ff>>(m, "wavelet_ff", D(wavelet_ff))

        .def(py::init(&wavelet_ff::make),
             py::arg("size") = 1024,
             py::arg("order") = 20,
             py::arg("forward") = true,
             D(wavelet_ff, make))


        ;
}
