/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:28:51 by dcandeia          #+#    #+#             */
/*   Updated: 2021/10/29 11:17:39 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t tam)
{
	size_t	i;

	i = 0;
	while (i < tam)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}