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
/* BINDTOOL_HEADER_FILE(fir_filter_blk.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(b7f37d8da8505f679fc1cade29097052)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/filter/fir_filter_blk.h>

template <class IN_T, class OUT_T, class TAP_T>
void bind_fir_filter_blk_template(py::module& m, const char* classname)
{
    using fir_filter_blk = gr::filter::fir_filter_blk<IN_T, OUT_T, TAP_T>;

    py::class_<fir_filter_blk,
               gr::sync_decimator,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<fir_filter_blk>>(m, classname)
        .def(py::init(&gr::filter::fir_filter_blk<IN_T, OUT_T, TAP_T>::make),
             py::arg("decimation"),
             py::arg("taps"))

        .def("set_taps", &fir_filter_blk::set_taps, py::arg("taps"))
        .def("taps", &fir_filter_blk::taps);
}

void bind_fir_filter_blk(py::module& m)
{
    bind_fir_filter_blk_template<gr_complex, gr_complex, gr_complex>(m, "fir_filter_ccc");
    bind_fir_filter_blk_template<gr_complex, gr_complex, float>(m, "fir_filter_ccf");
    bind_fir_filter_blk_template<float, gr_complex, gr_complex>(m, "fir_filter_fcc");
    bind_fir_filter_blk_template<float, float, float>(m, "fir_filter_fff");
    bind_fir_filter_blk_template<float, std::int16_t, float>(m, "fir_filter_fsf");
    bind_fir_filter_blk_template<std::int16_t, gr_complex, gr_complex>(m,
                                                                       "fir_filter_scc");
}
