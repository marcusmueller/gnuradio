/* -*- c++ -*- */
/*
 * Copyright 2006,2009,2010 Free Software Foundation, Inc.
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
#ifndef INCLUDED_PMT_INT_H
#define INCLUDED_PMT_INT_H

#include <pmt/pmt.h>
#include <boost/atomic.hpp>
#include <boost/utility.hpp>
#include <boost/version.hpp>
#include <utility>

/*
 * EVERYTHING IN THIS FILE IS PRIVATE TO THE IMPLEMENTATION!
 *
 * See pmt.h for the public interface
 */

namespace pmt {


class pmt_bool : public pmt_base
{
public:
    pmt_bool();
    //~pmt_bool(){}

    bool is_bool() const { return true; }
};


class pmt_symbol : public pmt_base
{
    std::string d_name;
    pmt_t d_next;

public:
    pmt_symbol(const std::string& name);
    //~pmt_symbol(){}

    bool is_symbol() const { return true; }
    const std::string name() { return d_name; }

    pmt_t next() { return d_next; } // symbol table link
    void set_next(pmt_t next) { d_next = std::move(next); }
};

class pmt_integer : public pmt_base
{
public:
    long d_value;

    pmt_integer(long value);
    //~pmt_integer(){}

    bool is_number() const { return true; }
    bool is_integer() const { return true; }
    long value() const { return d_value; }
};

class pmt_uint64 : public pmt_base
{
public:
    uint64_t d_value;

    pmt_uint64(uint64_t value);
    //~pmt_uint64(){}

    bool is_number() const { return true; }
    bool is_uint64() const { return true; }
    uint64_t value() const { return d_value; }
};

class pmt_real : public pmt_base
{
public:
    double d_value;

    pmt_real(double value);
    //~pmt_real(){}

    bool is_number() const { return true; }
    bool is_real() const { return true; }
    double value() const { return d_value; }
};

class pmt_complex : public pmt_base
{
public:
    std::complex<double> d_value;

    pmt_complex(std::complex<double> value);
    //~pmt_complex(){}

    bool is_number() const { return true; }
    bool is_complex() const { return true; }
    std::complex<double> value() const { return d_value; }
};

class pmt_null : public pmt_base
{
public:
    pmt_null();
    //~pmt_null(){}

    bool is_null() const { return true; }
};

class pmt_pair : public pmt_base
{
public:
    pmt_t d_car;
    pmt_t d_cdr;

    pmt_pair(const pmt_t& car, const pmt_t& cdr);
    //~pmt_pair(){};

    bool is_pair() const { return true; }
    pmt_t car() const { return d_car; }
    pmt_t cdr() const { return d_cdr; }

    void set_car(pmt_t car) { d_car = std::move(car); }
    void set_cdr(pmt_t cdr) { d_cdr = std::move(cdr); }
};

class pmt_vector : public pmt_base
{
    std::vector<pmt_t> d_v;

public:
    pmt_vector(size_t len, const pmt_t& fill);
    //~pmt_vector();

    bool is_vector() const { return true; }
    pmt_t ref(size_t k) const;
    void set(size_t k, pmt_t obj);
    void fill(const pmt_t& fill);
    size_t length() const { return d_v.size(); }

    pmt_t _ref(size_t k) const { return d_v[k]; }
};

class pmt_tuple : public pmt_base
{
    std::vector<pmt_t> d_v;

public:
    pmt_tuple(size_t len);
    //~pmt_tuple();

    bool is_tuple() const { return true; }
    pmt_t ref(size_t k) const;
    size_t length() const { return d_v.size(); }

    pmt_t _ref(size_t k) const { return d_v[k]; }
    void _set(size_t k, pmt_t v) { d_v[k] = std::move(v); }
};

class pmt_any : public pmt_base
{
    boost::any d_any;

public:
    pmt_any(const boost::any& any);
    //~pmt_any();

    bool is_any() const { return true; }
    const boost::any& ref() const { return d_any; }
    void set(const boost::any& any) { d_any = any; }
};


class pmt_uniform_vector : public pmt_base
{
public:
    bool is_uniform_vector() const { return true; }
    virtual const void* uniform_elements(size_t& len) = 0;
    virtual void* uniform_writable_elements(size_t& len) = 0;
    virtual size_t length() const = 0;
    virtual size_t itemsize() const = 0;
    virtual const std::string string_ref(size_t k) const
    {
        return std::string("not implemented");
    }
};
} /* namespace pmt */

#endif /* INCLUDED_PMT_INT_H */
