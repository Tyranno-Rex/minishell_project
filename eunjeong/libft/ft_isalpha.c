/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunjeong <eunjeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:53:52 by eunjeong          #+#    #+#             */
/*   Updated: 2022/07/25 16:57:38 by eunjeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int a)
{
	return ((a >= 65 && a <= 90) || (a >= 97 && a <= 122));
}