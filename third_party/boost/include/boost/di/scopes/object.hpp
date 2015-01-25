//
// Copyright (c) 2015 Francisco Javier Paz Menendez
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_SCOPES_OBJECT_HPP
#define BOOST_DI_SCOPES_OBJECT_HPP

#include "boost/di/wrappers/uniqueref.hpp"

#include <boost/mpl/int.hpp>

namespace boost {
namespace di {
namespace scopes {

class object_entry { };
class object_exit { };


template<template<typename> class TWrapper = wrappers::uniqueref>
class object
{
public:
    typedef mpl::int_<0> priority;

    template<typename TExpected>
    class scope
    {
    public:
        typedef TWrapper<TExpected> result_type;

        scope()
            : in_scope_(false)
        { }

        void call(const object_entry&) {
            in_scope_ = true;
        }

        void call(const object_exit&) {
            in_scope_ = false;
            object_.reset();
        }

        result_type create(const function<TExpected*()>& f) {
            if (!object_) {
                object_.reset(f());
            }
            return object_;
        }

    private:
        result_type object_;
        bool in_scope_;
    };
};

} // namespace scopes
} // namespace di
} // namespace boost

#endif
