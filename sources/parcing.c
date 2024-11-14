/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:41:16 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/14 17:37:38 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool		arg_check(int argc, char **argv);
t_dataset	*init_data(int argc, char **argv);
t_philo		*create_philos(t_dataset *data);
void		init_philo(t_philo *philo, t_dataset *data);

bool	arg_check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (false);
	while (i < argc)
	{
		if (!nbr_check(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

t_dataset	*init_data(int argc, char **argv)
{
	t_dataset	*data;

	data = (t_dataset *)malloc(sizeof(t_dataset));
	if (!data)
		return (NULL);
	data->seats = ft_atou(argv[1]);
	data->t_die = ft_atou(argv[2]);
	data->t_eat = ft_atou(argv[3]);
	data->t_spleep = ft_atou(argv[4]);
	data->game_over = false;
	pthread_mutex_init(&(data->print_lock), NULL);
	pthread_mutex_init(&(data->game_over_lock), NULL);
	if (argc == 6)
	{
		data->limit = true;
		data->eat_max = ft_atou(argv[5]);
	}
	else
	{
		data->limit = false;
		data->eat_max = 0;
	}
	return (data);
}

int	init_forks(t_dataset *data)
{
	t_philo	*pointer;
	int		i;

	pointer = &(*(data->first_philo));
	pointer->left_fork = (t_fork *)malloc(sizeof(t_fork));
	if (!(pointer->left_fork))
		return (EXIT_FAILURE);
	pointer->left_fork->free = true;
	pthread_mutex_init(&(pointer->left_fork->lock), NULL);
	i = 2;
	while (i <= data->seats)
	{
		pointer = &(*(pointer->left_philo));
		pointer->left_fork = (t_fork *)malloc(sizeof(t_fork));
		if (!(pointer->left_fork))
			return (EXIT_FAILURE);
		pointer->left_fork->free = true;
		pthread_mutex_init(&(pointer->left_fork->lock), NULL);
		pointer->right_fork = pointer->right_philo->left_fork;
		i++;
	}
	data->first_philo->right_fork = pointer->left_fork;
	return (EXIT_SUCCESS);
}

void	init_philo(t_philo *philo, t_dataset *data)
{
	philo->data = data;
	philo->left_fork_unlocked = true;
	philo->right_fork_unlocked = true;
	philo->printf_unlocked = true;
	pthread_mutex_init(&philo->last_meal_lock, NULL);
	pthread_mutex_init(&philo->times_eaten_lock, NULL);
}

t_philo	*create_philos(t_dataset *data)
{
	int			i;
	t_philo		*first;
	t_philo		*ptr_1;
	t_philo		*ptr_2;

	first = (t_philo *)malloc(sizeof(t_philo));
	if (!first)
		return (NULL);
	first->position = 1;
	init_philo(first, data);
	i = 2;
	ptr_1 = &(*first);
	while (i <= data->seats)
	{
		ptr_2 = (t_philo *)malloc(sizeof(t_philo));
		ptr_2->position = i;
		init_philo(ptr_2, data);
		ptr_1->left_philo = &(*ptr_2);
		ptr_2->right_philo = &(*ptr_1);
		ptr_1 = &(*ptr_2);
		i++;
	}
	ptr_1->left_philo = &(*first);
	first->right_philo = &(*ptr_1);
	return (first);
}
