#ifndef BOOST_MP11_UTILITY_HPP_INCLUDED
#define BOOST_MP11_UTILITY_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>

namespace boost
{

// mp_identity
template<class T> struct mp_identity
{
    using type = T;
};

// mp_inherit
template<class... T> struct mp_inherit: T... {};

// mp_if, mp_if_c
namespace detail
{

template<bool C, class T, class E> struct mp_if_c_impl;

template<class T, class E> struct mp_if_c_impl<true, T, E>
{
    using type = T;
};

template<class T, class E> struct mp_if_c_impl<false, T, E>
{
    using type = E;
};

} // namespace detail

template<bool C, class T, class E> using mp_if_c = typename detail::mp_if_c_impl<C, T, E>::type;
template<class C, class T, class E> using mp_if = typename detail::mp_if_c_impl<static_cast<bool>(C::value), T, E>::type;

// mp_eval_if, mp_eval_if_c
namespace detail
{

template<bool C, class T, template<class...> class F, class... U> struct mp_eval_if_c_impl;

template<class T, template<class...> class F, class... U> struct mp_eval_if_c_impl<true, T, F, U...>
{
    using type = T;
};

template<class T, template<class...> class F, class... U> struct mp_eval_if_c_impl<false, T, F, U...>
{
    using type = F<U...>;
};

} // namespace detail

template<bool C, class T, template<class...> class F, class... U> using mp_eval_if_c = typename detail::mp_eval_if_c_impl<C, T, F, U...>::type;
template<class C, class T, template<class...> class F, class... U> using mp_eval_if = typename detail::mp_eval_if_c_impl<static_cast<bool>(C::value), T, F, U...>::type;

// mp_valid
// implementation by Bruno Dutra (by the name is_evaluable)
namespace detail
{

template<template<class...> class F, class... T> struct mp_valid_impl
{
    template<template<class...> class G, class = G<T...>> static mp_true check(int);
    template<template<class...> class> static mp_false check(...);

    using type = decltype(check<F>(0));
};

} // namespace detail

template<template<class...> class F, class... T> using mp_valid = typename detail::mp_valid_impl<F, T...>::type;

// mp_defer
template<template<class...> class F, class... T> struct mp_defer
{
    using type = F<T...>;
};

// mp_defer_if_valid
template<template<class...> class F, class... T> using mp_defer_if_valid = mp_if<mp_valid<F, T...>, mp_defer<F, T...>, mp_inherit<>>;

} // namespace boost

#endif // #ifndef BOOST_MP11_UTILITY_HPP_INCLUDED