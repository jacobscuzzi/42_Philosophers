/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:14:53 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/18 20:11:39 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int		create_threads(t_dataset *data);
void	philo(t_philo *philo);
int		run_simulation(t_dataset *data);
void	uneaven_adjust(t_philo *philo);

void	philo(t_philo *philo)
{
	if (philo->position % 2 == 0)
	{
		if (grab_forks(philo) == EXIT_FAILURE)
			return ;
	}
	else
	{
		thinking(philo);
		usleep(1000);
		if (grab_forks(philo) == EXIT_FAILURE)
			return ;
	}
	while (1)
	{
		if (eating(philo) == EXIT_FAILURE)
			return ;
		if (sleeping(philo) == EXIT_FAILURE)
			return ;
		if (thinking(philo) == EXIT_FAILURE)
			return ;
		if (grab_forks(philo) == EXIT_FAILURE)
			return ;
	}
}

void	uneaven_adjust(t_philo *philo)
{
	unsigned int	t_eat;
	unsigned int 	think_max;

	t_eat = philo->data->t_eat;
	think_max = (philo->data->t_die - philo->data->t_eat - philo->data->t_spleep);
	if (philo->data->seats % 2 != 0)
	{
		// usleep(((2 * t_eat) - philo->data->t_spleep) * 1000);
		if ((t_eat * 1000) < (think_max * 1000))
		{
			usleep(t_eat * 1000);
		}
	}
	return ;
}
/*
bool	neighbour_more_hungry(t_philo	*philo)
{
	pthread_mutex_lock(&philo->left_philo->last_meal_lock);
	if (philo->left_philo->last_meal < philo->last_meal)
		return (pthread_mutex_unlock(&philo->left_philo->last_meal_lock), true);
	pthread_mutex_unlock(&philo->left_philo->last_meal_lock);
	pthread_mutex_lock(&philo->right_philo->last_meal_lock);
	if (philo->right_philo->last_meal < philo->last_meal)
		return (pthread_mutex_unlock(&philo->right_philo->last_meal_lock), true);
	pthread_mutex_unlock(&philo->right_philo->last_meal_lock);
	return (false);
}
*/

int	create_threads(t_dataset *data)
{
	t_philo	*ptr;
	int		i;

	ptr = &(*data->first_philo);
	if (pthread_create(&ptr->thread, NULL, (void *)&philo, ptr) != 0)
		return (EXIT_FAILURE);
	i = 2;
	while (i <= data->seats)
	{
		ptr = &(*ptr->left_philo);
		if (pthread_create(&ptr->thread, NULL, (void *)&philo, ptr) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	usleep(1000);
	if (pthread_create(&data->death_check, NULL, (void *)&livecheck, data) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	run_simulation(t_dataset *data)
{
	t_philo	*ptr;
	int		i;

	i = 1;
	if (create_threads(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	ptr = &*(data->first_philo);
	while (i <= data->seats)
	{
		pthread_join(ptr->thread, NULL);
		ptr = &*(ptr->left_philo);
		i++;
	}
	pthread_join(data->death_check, NULL);
	return (EXIT_SUCCESS);
}
