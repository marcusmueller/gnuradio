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

#include <gnuradio/log/log.h>
#include <gnuradio/log/threadsafe_queue.h>
#include <future>
#include <utility>
namespace gr {
namespace log {
logger& instance()
{
    static logger instance;
    return instance;
}
logger::logger() : running(true)
{
    // so far, everything delegated
    // TODO: spawn thread
    worker = std::thread(&logger::work, this);
}
void logger::work()
{
    while (running.load()) {
        try {
            auto& what = queue.pop();
            lock_t be_lock(backend_mutex);
            bool success = true;
            for (auto& be : backends) {
                try {
                    // TODO this should be std::async!
                    success = success && be->log(what);
                } catch (...) {
                    // logger failed.
                    // TODO remove logger from list
                }
            }
        } catch (...) {
            // I will not be disturbed by mere exceptions
        }
    }
}
logger::~logger() noexcept
{
    running = false;
    worker.join();
    try {
        while (true) {
            auto& entry = queue.pop_or_throw();
            {
                lock_t be_lock(backend_mutex);
                for (auto& be : backends) {
                    try {
                        be->log(entry);
                    } catch (...) {
                        // logger failed.
                        // since this is the destructor, we don't care.
                    }
                }
            }
        }
    } catch (const std::out_of_range& exception) {
        // queue empty. This is fine.
        for (auto& be : backends) {
            try {
                be->flush();
            } catch (...) {
                // logger failed to flush.
                // that's bad, but we're cleaning up the logging, so there's preciously
                // little we can do about that.
            }
        }
    }
}


void logger::attach(std::shared_ptr<backend> log_backend)
{
    lock_t lock(backend_mutex);
    backends.insert(log_backend);
}
void logger::detach(std::shared_ptr<backend> log_backend)
{
    lock_t lock(backend_mutex);
    for (auto iter = backends.begin(); iter != backends.end();) {
        if (*iter == log_backend) {
            iter = backends.erase(iter);
        } else {
            ++iter;
        }
    }
}
void logger::operator()(entry&& what) noexcept
{
    enqueue(std::move(what));
    // std::async(std::launch::async, &logger::enqueue, this, std::move(what));
}
void logger::enqueue(entry&& what) noexcept
{
    // TODO: filter by level whether to log at all.
    queue.push(std::move(what));
}
} // namespace log
} // namespace gr
