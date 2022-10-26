/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/* This file is automatically generated using bindtool */

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/qtgui/utils.h>
#include <qwt_legend.h>
#include <qwt_painter.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_zoomer.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_widget.h>
#include <qwt_symbol.h>

#include <gnuradio/qtgui/time_sink_f.h>
// pydoc.h is automatically generated in the build directory
#include <time_sink_f_pydoc.h>

void bind_time_sink_f(py::module& m)
{

    using time_sink_f = ::gr::qtgui::time_sink_f;


    py::class_<time_sink_f,
               gr::sync_block,
               gr::block,
               gr::basic_block,
               std::shared_ptr<time_sink_f>>(m, "time_sink_f", D(time_sink_f))

        .def(py::init(&time_sink_f::make),
             py::arg("size"),
             py::arg("samp_rate"),
             py::arg("name"),
             py::arg("nconnections") = 1,
             py::arg("parent") = nullptr,
             D(time_sink_f, make))


        .def("exec_", &time_sink_f::exec_, D(time_sink_f, exec_))


        .def(
            "qwidget",
            [](time_sink_f& self) { return reinterpret_cast<uintptr_t>(self.qwidget()); },
            D(time_sink_f, qwidget))


        .def("set_y_axis",
             &time_sink_f::set_y_axis,
             py::arg("min"),
             py::arg("max"),
             D(time_sink_f, set_y_axis))


        .def("set_y_label",
             &time_sink_f::set_y_label,
             py::arg("label"),
             py::arg("unit") = "",
             D(time_sink_f, set_y_label))


        .def("set_update_time",
             &time_sink_f::set_update_time,
             py::arg("t"),
             D(time_sink_f, set_update_time))


        .def("set_title",
             &time_sink_f::set_title,
             py::arg("title"),
             D(time_sink_f, set_title))


        .def("set_line_label",
             &time_sink_f::set_line_label,
             py::arg("which"),
             py::arg("line"),
             D(time_sink_f, set_line_label))


        .def("set_line_color",
             &time_sink_f::set_line_color,
             py::arg("which"),
             py::arg("color"),
             D(time_sink_f, set_line_color))


        .def("set_line_width",
             &time_sink_f::set_line_width,
             py::arg("which"),
             py::arg("width"),
             D(time_sink_f, set_line_width))


        .def("set_line_style",
             &time_sink_f::set_line_style,
             py::arg("which"),
             py::arg("style"),
             D(time_sink_f, set_line_style))


        .def("set_line_marker",
             &time_sink_f::set_line_marker,
             py::arg("which"),
             py::arg("marker"),
             D(time_sink_f, set_line_marker))


        .def("set_nsamps",
             &time_sink_f::set_nsamps,
             py::arg("newsize"),
             D(time_sink_f, set_nsamps))


        .def("set_samp_rate",
             &time_sink_f::set_samp_rate,
             py::arg("samp_rate"),
             D(time_sink_f, set_samp_rate))


        .def("set_line_alpha",
             &time_sink_f::set_line_alpha,
             py::arg("which"),
             py::arg("alpha"),
             D(time_sink_f, set_line_alpha))


        .def("set_trigger_mode",
             &time_sink_f::set_trigger_mode,
             py::arg("mode"),
             py::arg("slope"),
             py::arg("level"),
             py::arg("delay"),
             py::arg("channel"),
             py::arg("tag_key") = "",
             D(time_sink_f, set_trigger_mode))


        .def("title", &time_sink_f::title, D(time_sink_f, title))


        .def("line_label",
             &time_sink_f::line_label,
             py::arg("which"),
             D(time_sink_f, line_label))


        .def("line_color",
             &time_sink_f::line_color,
             py::arg("which"),
             D(time_sink_f, line_color))


        .def("line_width",
             &time_sink_f::line_width,
             py::arg("which"),
             D(time_sink_f, line_width))


        .def("line_style",
             &time_sink_f::line_style,
             py::arg("which"),
             D(time_sink_f, line_style))


        .def("line_marker",
             &time_sink_f::line_marker,
             py::arg("which"),
             D(time_sink_f, line_marker))


        .def("line_alpha",
             &time_sink_f::line_alpha,
             py::arg("which"),
             D(time_sink_f, line_alpha))


        .def("set_size",
             &time_sink_f::set_size,
             py::arg("width"),
             py::arg("height"),
             D(time_sink_f, set_size))


        .def("enable_menu",
             &time_sink_f::enable_menu,
             py::arg("en") = true,
             D(time_sink_f, enable_menu))


        .def("enable_grid",
             &time_sink_f::enable_grid,
             py::arg("en") = true,
             D(time_sink_f, enable_grid))


        .def("enable_autoscale",
             &time_sink_f::enable_autoscale,
             py::arg("en") = true,
             D(time_sink_f, enable_autoscale))


        .def("enable_stem_plot",
             &time_sink_f::enable_stem_plot,
             py::arg("en") = true,
             D(time_sink_f, enable_stem_plot))


        .def("enable_semilogx",
             &time_sink_f::enable_semilogx,
             py::arg("en") = true,
             D(time_sink_f, enable_semilogx))


        .def("enable_semilogy",
             &time_sink_f::enable_semilogy,
             py::arg("en") = true,
             D(time_sink_f, enable_semilogy))


        .def("enable_control_panel",
             &time_sink_f::enable_control_panel,
             py::arg("en") = true,
             D(time_sink_f, enable_control_panel))


        .def("enable_tags",
             (void(time_sink_f::*)(unsigned int, bool)) & time_sink_f::enable_tags,
             py::arg("which"),
             py::arg("en"),
             D(time_sink_f, enable_tags, 0))


        .def("enable_tags",
             (void(time_sink_f::*)(bool)) & time_sink_f::enable_tags,
             py::arg("en"),
             D(time_sink_f, enable_tags, 1))


        .def("enable_axis_labels",
             &time_sink_f::enable_axis_labels,
             py::arg("en") = true,
             D(time_sink_f, enable_axis_labels))


        .def("disable_legend",
             &time_sink_f::disable_legend,
             D(time_sink_f, disable_legend))


        .def("nsamps", &time_sink_f::nsamps, D(time_sink_f, nsamps))


        .def("reset", &time_sink_f::reset, D(time_sink_f, reset))

        ;
}
