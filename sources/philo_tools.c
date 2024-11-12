/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:51:21 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/12 18:05:15 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool			nbr_check(char *string);
bool			ft_isdigit(int c);
unsigned int	ft_atou(const char *str);
unsigned int	get_ts(t_dataset *data);

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

unsigned int	get_ts(t_dataset *data)
{
	struct timeval	time_now;
	struct timeval	time_start;
	unsigned int	elapsed_sec;
	unsigned int	elapsed_microsec;
	unsigned int	elapsed_milisec;

	gettimeofday(&time_now, NULL);
	time_start = data->time_start;
	elapsed_sec = (unsigned int)(time_now.tv_sec - time_start.tv_sec);
	elapsed_microsec = (unsigned int)(time_now.tv_usec - time_start.tv_usec);
	elapsed_milisec = elapsed_sec * 1000 + elapsed_microsec / 1000;
	return (elapsed_milisec);
}

void	kill_philo(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->lock);
	pthread_mutex_unlock(&philo->right_fork->lock);
}

/*
void	print_philos(t_philo *first)
{
	t_philo	*pointer;

	pointer = first;
	printf("Philosopher Nr %u (Right Fork: %p  Left Fork: %p) \n"
		, pointer->position, pointer->right_fork, pointer->left_fork);
	pointer = first->left_philo;
	while (pointer->position > 1)
	{
		printf("Philosopher Nr %u (Right Fork: %p  Left Fork: %p)\n"
		, pointer->position, pointer->right_fork, pointer->left_fork);
		pointer = pointer->left_philo;
	}
}
*/
