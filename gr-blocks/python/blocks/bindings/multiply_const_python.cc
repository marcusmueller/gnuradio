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
/* BINDTOOL_HEADER_FILE(multiply_const.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(428355ad5ce3ba934e91d0464aacb354)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/blocks/multiply_const.h>

template <typename T>
void bind_multiply_const_template(py::module& m, const char* classname)
{
    using multiply_const = gr::blocks::multiply_const<T>;

    py::class_<multiply_const,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<multiply_const>>(m, classname)
        .def(py::init(&gr::blocks::multiply_const<T>::make),
             py::arg("k"),
             py::arg("vlen") = 1)
        .def("k", &multiply_const::k)
        .def("set_k", &multiply_const::set_k, py::arg("k"));
}

void bind_multiply_const(py::module& m)
{
    bind_multiply_const_template<std::int16_t>(m, "multiply_const_ss");
    bind_multiply_const_template<std::int32_t>(m, "multiply_const_ii");
    bind_multiply_const_template<float>(m, "multiply_const_ff");
    bind_multiply_const_template<gr_complex>(m, "multiply_const_cc");
}
