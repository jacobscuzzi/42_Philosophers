/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:15:19 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/10/29 03:31:19 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

bool	arg_check(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (false);
	while (argv[i])
	{
		if (!nbr_check(argv[i]))
			return (false);
	}
}

t_dataset	*init_data(int argc, char **argv)
{
	t_dataset	*data;

	data = (t_dataset)malloc(sizeof(t_dataset));
	if (!table)
		return (NULL);
	data->seats = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_spleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->limit = true;
		data->nbr_eat = ft_atoi(argv[5]);
	}
	return (data);
}
int	main(int argc, char **argv)
{
	if (!arg_check(argc, argv))
		return (EXIT_FAILURE);
}
