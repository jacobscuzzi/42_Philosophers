/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:49:34 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/10 16:54:56 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	thinking(t_philo *philo);
void	grab_forks(t_philo *philo);
void	eating(t_philo *philo);


void	thinking(t_philo *philo)
{
	printf("%u %d is thinking\n", get_ts(philo->data), philo->position);
}

void	grab_forks(t_philo *philo)
{
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
	eating(philo);
}
void	eating(t_philo *philo)
{
	printf("%u %d is eating\n", get_ts(philo->data), philo->position);
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->lock);
	pthread_mutex_unlock(&philo->right_fork->lock);
}
