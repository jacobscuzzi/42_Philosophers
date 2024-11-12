/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:14:53 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/12 18:14:51 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_threads(t_dataset *data);
void	philo(t_philo *philo);
int	run_simulation(t_dataset *data);

void philo(t_philo *philo)
{
	philo->times_eaten = 0;
	philo->last_meal = 0;
	thinking(philo);
	if (philo->position % 2 == 0)
	{
		if (grab_forks(philo) == EXIT_FAILURE)
			return ;
	}
	else
	{
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
		if (grab_forks(philo) == EXIT_FAILURE)
			return ;
	}
}

bool	mealcheck(t_dataset *data)
{
	t_philo	*ptr;
	int		limit;

	limit = data->eat_max;
	ptr = &(*data->first_philo);
	if (ptr->times_eaten < limit)
		return (false);
	ptr = &(*ptr->left_philo);
	while (ptr->position != 1)
	{
		if (ptr->times_eaten < limit)
			return (false);
		ptr = &(*ptr->left_philo);
	}
	return (true);
}

void	livecheck(t_dataset *data)
{
	t_philo			*ptr;

	while (1)
	{
		if (data->limit == true)
		{
			if (mealcheck(data))
			{
				philos_full(data);
				return ;
			}
		}
		ptr = &(*data->first_philo);
		if (data->t_die < get_ts(data) - ptr->last_meal)
		{
			philo_dead(ptr);
			return ;
		}
		ptr = &(*ptr->left_philo);
		while (ptr->position != 1)
		{
			if (data->t_die < get_ts(data) - ptr->last_meal)
			{
				philo_dead(ptr);
				return ;
			}
			ptr = &(*ptr->left_philo);
		}
		usleep(100);
	}
}

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
