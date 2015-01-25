//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_BINDINGS_DETAIL_WHEN_HPP
#define BOOST_DI_BINDINGS_DETAIL_WHEN_HPP

#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/empty.hpp>

namespace boost {
namespace di {
namespace bindings {
namespace detail {

template<typename TContext>
class when_
{
    template<
        typename TBind
      , typename T
    >
    struct apply_bind
        : TBind::template apply<T>::type
    { };

public:
    template<typename T>
    struct apply
        : mpl::if_<
              mpl::empty<TContext>
            , mpl::int_<1>
            , typename mpl::deref<
                  mpl::max_element<
                      mpl::transform_view<
                          TContext
                        , apply_bind<mpl::_1, T>
                      >
                  >
              >::type
          >::type
    { };
};

} // namespace detail
} // namespace bindings
} // namespace di
} // namespace boost

#endif

