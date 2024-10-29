/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:15:19 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/10/29 18:24:57 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool		arg_check(int argc, char **argv);
t_dataset	*init_data(int argc, char **argv);
int			main(int argc, char **argv);
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

t_philo		*init_philos(t_dataset *data)
{
	int			i;
	t_philo		*first;
	t_philo		*pointer_1;
	t_philo		*pointer_2;

	first = (t_philo *)malloc(sizeof(t_philo));
	first->position = 1;
	i = 2;
	pointer_1 = first;
	while (i <= data->seats)
	{
		pointer_2 = (t_philo *)malloc(sizeof(t_philo));
		pointer_2->position = i;
		pointer_1->left_philo = &(*pointer_2);
		pointer_2->right_philo = &(*pointer_1);
		pointer_1 = &(*pointer_2);
		i++;
	}
	pointer_2->left_philo = &(*first);
	first->right_philo = &(*pointer_2);
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
	data->first_philo = init_philos(data);
	if (!(data->first_philo))
		return (EXIT_FAILURE);
	printf("Philos initialized\n");
	print_philos(data->first_philo);
}
