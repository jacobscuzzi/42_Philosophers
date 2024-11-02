/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:41:16 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/02 22:30:02 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool		arg_check(int argc, char **argv);
t_dataset	*init_data(int argc, char **argv);
t_philo		*init_philos(t_dataset *data);


bool	arg_check(int argc, char **argv)
{
	int	i;

	printf("starting arg check\n");
	i = 1;
	if (argc != 5 && argc != 6)
		return (false);
	while (i < argc)
	{
		printf("checking argument %d\n", i);
		if (!nbr_check(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

void	*init_thread(t_dataset *datat)
{
	printf("Thread was created\n");
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
	if (argc == 6)
	{
		data->limit = true;
		data->nbr_eat = ft_atou(argv[5]);
	}
	return (data);
}

int		init_forks(t_dataset *data)
{
	t_philo	*pointer;
	int i;

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

t_philo		*init_philos(t_dataset *data)
{
	int			i;
	t_philo		*first;
	t_philo		*ptr_1;
	t_philo		*ptr_2;

	first = (t_philo *)malloc(sizeof(t_philo));
	if (!first)
		return (NULL);
	first->position = 1;
	if (pthread_create(&(first->thread), NULL, (void *)&init_thread, data) != 0)
		return (NULL);
	pthread_join(first->thread, NULL);
	i = 2;
	ptr_1 = &(*first);
	while (i <= data->seats)
	{
		ptr_2 = (t_philo *)malloc(sizeof(t_philo));
		ptr_2->position = i;
		if (pthread_create(&(ptr_2->thread), NULL, (void *)&init_thread, NULL) != 0)
			return (NULL);
		pthread_join(ptr_2->thread, NULL);
		ptr_1->left_philo = &(*ptr_2);
		ptr_2->right_philo = &(*ptr_1);
		ptr_1 = &(*ptr_2);
		i++;
	}
	ptr_1->left_philo = &(*first);
	first->right_philo = &(*ptr_1);
	return (first);
}
