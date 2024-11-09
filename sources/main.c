/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:15:19 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/09 01:42:10 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_phillo(t_philo *philo)
{
	if (philo->left_philo && philo->left_philo->position != 1)
		free_phillo(philo->left_philo);
	if (philo->left_fork)
	{
		free(philo->left_fork);
	}
	free(philo);
}

void	free_data(t_dataset *data)
{
	free_phillo(data->first_philo);
	free(data);
}

int	main(int argc, char **argv)
{
	t_dataset	*data;
	t_philo		*first_philo;

	if (!arg_check(argc, argv))
		return (EXIT_FAILURE);
	printf("Argument checked\n");
	data = init_data(argc, argv);
	if (!data)
		return (EXIT_FAILURE);
	printf("Data initialized\n");
	gettimeofday(&(data->start_time), NULL);
	data->first_philo = init_philos(data);
	if (!(data->first_philo))
		return (free(data), EXIT_FAILURE);
	printf("Philos initialized\n");
	if (init_forks(data) == EXIT_FAILURE)
		return (free_data(data), EXIT_FAILURE);
	printf("Forks initialized\n");
	print_philos(data->first_philo);
	if (run_simulation(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free_data(data);
	return (EXIT_SUCCESS);
}
