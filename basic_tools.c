/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 00:52:22 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/10/29 03:24:29 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

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
		if (string[i] < '0' || string[i] > 9)
			return (false);
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	counter;
	int	negator;

	negator = 1;
	i = 0;
	counter = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negator *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		counter = counter * 10 + str[i] - 48;
		i++;
	}
	return (counter * negator);
}

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	else
		return (1);
}