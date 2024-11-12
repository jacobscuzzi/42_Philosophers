/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:49:34 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/12 18:12:16 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int		thinking(t_philo *philo);
int		grab_forks(t_philo *philo);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);


int	still_alive(t_dataset *data)
{
	if (data->game_over == true)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

int	thinking(t_philo *philo)
{
	if (still_alive(philo->data) == EXIT_FAILURE)
		return (kill_philo(philo), EXIT_FAILURE);
	printf("%u %d is thinking\n", get_ts(philo->data), philo->position);
	return (EXIT_SUCCESS);
}

int	grab_forks(t_philo *philo)
{
	if (still_alive(philo->data) == EXIT_FAILURE)
		return (kill_philo(philo), EXIT_FAILURE);
	if (philo->position % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->lock);
		printf("%u %d has taken a fork\n", get_ts(philo->data), philo->position);
		pthread_mutex_lock(&philo->right_fork->lock);
		printf("%u %d has taken a fork\n", get_ts(philo->data), philo->position);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->lock);
		printf("%u %d has taken a fork\n", get_ts(philo->data), philo->position);
		pthread_mutex_lock(&philo->left_fork->lock);
		printf("%u %d has taken a fork\n", get_ts(philo->data), philo->position);
	}
	return (EXIT_SUCCESS);
}

int	eating(t_philo *philo)
{
	if (still_alive(philo->data) == EXIT_FAILURE)
		return (kill_philo(philo), EXIT_FAILURE);
	printf("%u %d is eating\n", get_ts(philo->data), philo->position);
	philo->last_meal = get_ts(philo->data);
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->lock);
	pthread_mutex_unlock(&philo->right_fork->lock);
	philo->last_meal = get_ts(philo->data);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *philo)
{
	if (still_alive(philo->data) == EXIT_FAILURE)
		return (kill_philo(philo), EXIT_FAILURE);
	printf("%u %d is sleeping\n", get_ts(philo->data), philo->position);
	usleep(philo->data->t_spleep * 1000);
	return (EXIT_SUCCESS);
}
