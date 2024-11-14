/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:49:43 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/14 18:30:39 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	livecheck(t_dataset *data);
bool	mealcheck(t_dataset *data);

bool	game_over_check(t_dataset *data)
{
	pthread_mutex_lock(&data->game_over_lock);
	if (data->game_over == true)
	{
		pthread_mutex_unlock(&data->game_over_lock);
		return (true);
	}
	pthread_mutex_unlock(&data->game_over_lock);
	return (false);
}

bool	still_hungry(t_philo *philo)
{
	unsigned int	limit;

	limit = philo->data->eat_max;
	pthread_mutex_lock(&philo->times_eaten_lock);
	if (philo->times_eaten < limit)
	{
		pthread_mutex_unlock(&philo->times_eaten_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->times_eaten_lock);
		return (false);
	}
}

bool	mealcheck(t_dataset *data)
{
	t_philo			*ptr;

	if (data->limit == false)
		return (false);
	else
	{
		ptr = &(*data->first_philo);
		if (still_hungry(ptr) == true)
			return (false);
		ptr = &(*ptr->left_philo);
		while (ptr->position != 1)
		{
			if (still_hungry(ptr) == true)
				return (false);
			ptr = &(*ptr->left_philo);
		}
		pthread_mutex_lock(&data->game_over_lock);
		data->game_over = true;
		pthread_mutex_unlock(&data->game_over_lock);
		return (true);
	}
}

bool	still_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_lock);
	if (philo->data->t_die <= (get_ts(philo->data) - philo->last_meal))
	{
		pthread_mutex_unlock(&philo->last_meal_lock);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&philo->last_meal_lock);
		return (true);
	}
}

void	livecheck(t_dataset *data)
{
	t_philo			*ptr;

	while (1)
	{
		if (mealcheck(data) == true)
			return ;
		ptr = &(*data->first_philo);
		if (still_alive(ptr) == false)
		{
			philo_dead(ptr);
			return ;
		}
		ptr = &(*ptr->left_philo);
		while (ptr->position != 1)
		{
			if (still_alive(ptr) == false)
			{
				philo_dead(ptr);
				return ;
			}
			ptr = &(*ptr->left_philo);
		}
		usleep(1000);
	}
}