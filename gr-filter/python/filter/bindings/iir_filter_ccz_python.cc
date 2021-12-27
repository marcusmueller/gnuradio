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
/* BINDTOOL_HEADER_FILE(iir_filter_ccz.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(8ddca335025ee53cc6c3fccf2aa8fb72)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/filter/iir_filter_ccz.h>
// pydoc.h is automatically generated in the build directory
#include <iir_filter_ccz_pydoc.h>

void bind_iir_filter_ccz(py::module& m)
{

    using iir_filter_ccz = ::gr::filter::iir_filter_ccz;


    py::class_<iir_filter_ccz,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<iir_filter_ccz>>(m, "iir_filter_ccz", D(iir_filter_ccz))

        .def(py::init(&iir_filter_ccz::make),
             py::arg("fftaps"),
             py::arg("fbtaps"),
             py::arg("oldstyle") = true,
             D(iir_filter_ccz, make))


        .def("set_taps",
             &iir_filter_ccz::set_taps,
             py::arg("fftaps"),
             py::arg("fbtaps"),
             D(iir_filter_ccz, set_taps))

        ;
}
