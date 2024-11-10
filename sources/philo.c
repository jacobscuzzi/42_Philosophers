/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:14:53 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/10 16:19:03 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_threads(t_dataset *data);
void	philo(t_philo *philo);
int	run_simulation(t_dataset *data);

void philo(t_philo *philo)
{
	thinking(philo);
	if (philo->position % 2 == 0)
		grab_forks(philo);
	else
	{
		usleep(1000);
		grab_forks(philo);
	}
}


int	create_threads(t_dataset *data)
{
	t_philo	*ptr;
	int		i;

	ptr = &(*data->first_philo);
	if (pthread_create(&ptr->thread, NULL, (void *)&philo, ptr) != 0)
		return (EXIT_FAILURE);
	printf("First Thread created\n");
	i = 2;
	while (i <= data->seats)
	{
		ptr = &(*ptr->left_philo);
		if (pthread_create(&ptr->thread, NULL, (void *)&philo, ptr) != 0)
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
	printf("Threads created\n");
	ptr = &*(data->first_philo);
	while (i < data->seats)
	{
		pthread_join(ptr->thread, NULL);
		ptr = &*(ptr->left_philo);
		i++;
	}
	return (EXIT_SUCCESS);
}
