//
// Copyright (c) 2015 Francisco Javier Paz Menendez
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_WRAPPERS_UNIQUEREF_HPP
#define BOOST_DI_WRAPPERS_UNIQUEREF_HPP

#include "boost/di/aux_/memory.hpp"

namespace boost {
namespace di {
namespace wrappers {

template<typename T>
class uniqueref
{
public:
    uniqueref()
        : value_(nullptr)
    { }

    uniqueref(T* value) // non explicit
        : value_(value)
    { }

    bool operator!() const {
        return !value_;
    }

    void reset(T* ptr = nullptr) {
        value_ = ptr;
    }

    template<typename I>
    aux::unique_ptr<I> operator()(const type<aux::unique_ptr<I> >&) const {
        return aux::unique_ptr<I>(value_);
    }

    template<typename I>
    I& operator()(const type<I&> &) const {
        return *value_;
    }

    template<typename I>
    const I& operator()(const type<const I&> &) const {
        return *value_;
    }

private:
    T* value_;
};

} // namespace wrappers
} // namespace di
} // namespace boost

#endif
