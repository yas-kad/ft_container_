/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <yait-kad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:15:23 by yait-kad          #+#    #+#             */
/*   Updated: 2022/02/24 15:16:03 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
    //TODO - Define enable_if
    template <bool Cond, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };
}

#endif