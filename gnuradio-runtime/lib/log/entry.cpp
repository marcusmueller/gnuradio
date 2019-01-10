/*
 * Copyright 2018 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <gnuradio/log/entry.h>
#include <chrono>
#include <tuple>
namespace gr {
namespace log {
const char* severity_to_string(const severity level)
{
    switch (level) {
    case trace:
        return "TRACE";
    case debug:
        return "DEBUG";
    case info:
        return "INFO";
    case warning:
        return "WARNING";
    case error:
        return "ERROR";
    case fatal:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}
bool operator<(const entry& left, const entry& right)
{
    return std::tie(left.time, left.level, left.source, left.purpose, left.message) >
           std::tie(right.time, right.level, right.source, right.purpose, right.message);
}
entry::entry(severity level, std::string source, std::string purpose, std::string message)
    : time(std::chrono::system_clock::now()),
      level(level),
      source(std::move(source)),
      purpose(std::move(purpose)),
      message(std::move(message))
{
    // for now, everything is in the initialization list
}

} // namespace log
} // namespace gr
