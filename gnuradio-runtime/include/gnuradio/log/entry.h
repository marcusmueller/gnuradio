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

#ifndef INCLUDED_GR_RUNTIME_RUNTIME_LOG_ENTRY_H
#define INCLUDED_GR_RUNTIME_RUNTIME_LOG_ENTRY_H
#include <gnuradio/api.h>
#include <chrono>
#include <memory>
#include <string>
namespace gr {
namespace log {

/*! Severity enumeration
 */
enum severity { trace, debug, info, warning, error, fatal };
/*! converts severity values to C string
 */
const char* GR_RUNTIME_API severity_to_string(const severity level);


/*! Immutable, uncopyable log entry class
 * This is used internally to move(!) log entries through the system.
 * You cannot log anything other than either calling
 * `auto& logger = gr::log::instance(); logger(entry(level, src, purpose, msg));`
 * or using move semantics:
 * `auto log_entry = entry(level, src, purpose, msg); logger(std::move(log_entry));`
 * Point is that there can be only one data-carrying instance of a log message.
 * This ensures zero-copy logging as well as involuntary later in-place modification
 * cannot happen.
 */
class GR_RUNTIME_API entry
{
public:
    entry(const entry&) = delete; //! no copy constructor
    /*! default move constructor. When passing an entry, the ownership is transferred.
     * Every time.
     */
    entry(entry&& source) = default;
    /*! Constructor for a log entry.
     * \param level the severity of the log entry
     * \param source a string representing the source
     * \param purpose a string specifying the reason this was logged. E.g.: source =
     * ofdm_receiver_block; purpose = preamble;
     * \param message the actual log message. At
     * construction time, the current time is assigned to the internal timestamp, so
     * create in-place.
     */
    entry(severity level, std::string source, std::string purpose, std::string entry);

    const std::chrono::time_point<std::chrono::system_clock>
        time;             //! the time at log entry creation
    const severity level; //! severity of the log entry
    std::string source;   //! source of the log message
    std::string purpose;  //! reason within the source this was logged
    std::string message;  //! log message

    friend bool operator<(const entry& left, const entry& right);
};
} // namespace log
} // namespace gr
#endif /* INCLUDED_GR_RUNTIME_RUNTIME_LOG_ENTRY_H */
