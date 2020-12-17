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
/* BINDTOOL_HEADER_FILE(constellation_encoder_bc.h) */
/* BINDTOOL_HEADER_FILE_HASH(b7a40d63f0e359222f614398dd1483a3)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/digital/constellation_encoder_bc.h>
// pydoc.h is automatically generated in the build directory
#include <constellation_encoder_bc_pydoc.h>

void bind_constellation_encoder_bc(py::module& m)
{

    using constellation_encoder_bc = ::gr::digital::constellation_encoder_bc;

    py::class_<constellation_encoder_bc,
               gr::sync_interpolator,
               std::shared_ptr<constellation_encoder_bc>>(
        m, "constellation_encoder_bc", D(constellation_encoder_bc))

        .def(py::init(&constellation_encoder_bc::make),
             py::arg("constellation"),
             D(constellation_encoder_bc, make));
}
