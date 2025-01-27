/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:51:21 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/15 15:57:23 by jbaumfal         ###   ########.fr       */
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
	unsigned int	elapsed_ms;

	gettimeofday(&time_now, NULL);
	time_start = data->time_start;
	elapsed_ms = (unsigned int)(((time_now.tv_sec - time_start.tv_sec) * 1000)
			+ ((time_now.tv_usec - time_start.tv_usec) / 1000));
	return (elapsed_ms);
}

void	kill_philo(t_philo *philo, int flag)
{
	if (flag == NO_LOCK)
		return ;
	if (flag == LEFT_FORK || flag == BOTH_FORKS)
		pthread_mutex_unlock(&philo->left_fork->lock);
	if (flag == RIGHT_FORK || flag == BOTH_FORKS)
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
