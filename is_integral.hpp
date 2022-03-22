/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <yait-kad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:17:21 by yait-kad          #+#    #+#             */
/*   Updated: 2022/02/24 15:17:24 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <iostream>

namespace ft
{
    //TODO - Define Is integral
    template <class T> 
    struct is_integral
    {
        static const bool value = false;
    };
    template <>
    struct is_integral<char>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<char16_t>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<char32_t>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<wchar_t>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<signed char>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<short int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<long long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned char>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned short int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<unsigned long long int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<float>
    {
        static const bool value = true;
    };
}

#endif