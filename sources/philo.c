/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:14:53 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/09 02:14:57 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo(t_philo *philo)
{
	printf("Philosopher was created\n");
}

void	thinking(t_philo *philo)
{
	printf("Philosopher is  \n");
}
int	create_threads(t_dataset *data)
{
	t_philo	*pointer;
	int		i;

	pointer = &(*data->first_philo);
	if (pthread_create(&pointer->thread, NULL, (void *)&philo, data) != 0)
		return (EXIT_FAILURE);
	i = 2;
	while (i <= data->seats)
	{
		pointer = &(*pointer->left_philo);
		if (pthread_create(&pointer->thread, NULL, (void *)&philo, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	run_simulation(t_dataset *data)
{
	t_philo	*ptr;
	int		i;

	i = 1;
	printf("Startig Simulation\n");
	if (create_threads(data) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	ptr = &*(data->first_philo);
	while (i < data->seats)
	{
		pthread_join(ptr->thread, NULL);
		ptr = &*(ptr->left_philo);
		i++;
	}
	return (EXIT_SUCCESS);
}
