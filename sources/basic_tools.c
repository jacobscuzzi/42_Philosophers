/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 00:52:22 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/10/29 18:11:05 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool			nbr_check(char *string);
bool			ft_isdigit(int c);
unsigned int	ft_atou(const char *str);

bool	nbr_check(char *string)
{
	int	i;

	i = 0;
	while (string[i] == ' ')
		i++;
	if (!string[i])
		return (false);
	while (string[i])
	{
		if (!(ft_isdigit(string[i])))
			return (false);
		i++;
	}
	return (true);
}

unsigned int	ft_atou(const char *str)
{
	int				i;
	unsigned int	counter;

	i = 0;
	counter = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		counter = counter * 10 + str[i] - 48;
		i++;
	}
	return (counter);
}

bool	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (false);
	else
		return (true);
}
