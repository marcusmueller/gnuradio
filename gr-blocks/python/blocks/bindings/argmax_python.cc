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
/* BINDTOOL_HEADER_FILE(argmax.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(05ae1258982c0139edac2164d9db55d1)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/argmax.h>

template <typename T>
void bind_argmax_template(py::module& m, const char* classname)
{
    using argmax = gr::blocks::argmax<T>;

    py::class_<argmax,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<argmax>>(m, classname)
        .def(py::init(&gr::blocks::argmax<T>::make));
}

void bind_argmax(py::module& m)
{
    bind_argmax_template<std::int16_t>(m, "argmax_ss");
    bind_argmax_template<std::int32_t>(m, "argmax_is");
    bind_argmax_template<float>(m, "argmax_fs");
}
