/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:51:21 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/10/29 18:02:17 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_philos(t_philo *first)
{
	t_philo	*pointer;

	pointer = first;
	printf("Philosopher Nr %u\n", pointer->position);
	pointer = first->left_philo;
	while (pointer->position > 1)
	{
		printf("Philosopher Nr %u\n", pointer->position);
		pointer = first->left_philo;
	}

}
