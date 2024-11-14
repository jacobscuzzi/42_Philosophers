/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:49:34 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/14 18:38:47 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int		philo_print(t_philo *philo, char *string);
int		thinking(t_philo *philo);
int		grab_forks(t_philo *philo);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);

int	philo_print(t_philo *philo, char *string)
{
	if (game_over_check(philo->data) == true)
		return (kill_philo, EXIT_FAILURE);
	philo->printf_unlocked = false;
	pthread_mutex_lock(&(philo->data->print_lock));
	printf("%u %d %s\n", get_ts(philo->data), philo->position, string);
	philo->printf_unlocked = true;
	pthread_mutex_unlock(&(philo->data->print_lock));
	return (EXIT_SUCCESS);
}

int	thinking(t_philo *philo)
{
	if (philo_print(philo, "is thinking") == EXIT_FAILURE)
		return (kill_philo(philo), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	grab_forks(t_philo *philo)
{
	if (game_over_check(philo->data) == true)
		return (kill_philo, EXIT_FAILURE);
	if (philo->position % 2 == 0)
	{
		philo->left_fork_unlocked = false;
		pthread_mutex_lock(&philo->left_fork->lock);
		if (philo_print(philo, "has taken a fork") == EXIT_FAILURE)
			return (kill_philo(philo), EXIT_FAILURE);
		philo->right_fork_unlocked = false;
		pthread_mutex_lock(&philo->right_fork->lock);
		if (philo_print(philo, "has taken a fork") == EXIT_FAILURE)
			return (kill_philo(philo), EXIT_FAILURE);
	}
	else
	{
		philo->right_fork_unlocked = false;
		pthread_mutex_lock(&philo->right_fork->lock);
		if (philo_print(philo, "has taken a fork") == EXIT_FAILURE)
			return (kill_philo(philo), EXIT_FAILURE);
		philo->left_fork_unlocked = false;
		pthread_mutex_lock(&philo->left_fork->lock);
		if (philo_print(philo, "has taken a fork") == EXIT_FAILURE)
			return (kill_philo(philo), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	eating(t_philo *philo)
{
	if (philo_print(philo, "is eating") == EXIT_FAILURE)
		return (kill_philo(philo), EXIT_FAILURE);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_ts(philo->data);
	pthread_mutex_unlock(&philo->last_meal_lock);
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->lock);
	philo->left_fork_unlocked = true;
	pthread_mutex_unlock(&philo->right_fork->lock);
	philo->right_fork_unlocked = true;
	pthread_mutex_lock(&philo->times_eaten_lock);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_lock);
	return (EXIT_SUCCESS);
}

int	sleeping(t_philo *philo)
{
	if (philo_print(philo, "is sleeping") == EXIT_FAILURE)
		return (kill_philo(philo), EXIT_FAILURE);
	usleep(philo->data->t_spleep * 1000);
	return (EXIT_SUCCESS);
}
