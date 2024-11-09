/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:51:21 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/08 19:42:22 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_philos(t_philo *first)
{
	t_philo	*pointer;

	pointer = first;
	printf("Philosopher Nr %u (Right Fork: %p  Left Fork: %p) \n"
		, pointer->position, pointer->right_fork, pointer->left_fork);
	pointer = first->left_philo;
	while (pointer->position > 1)
	{
		printf("Philosopher Nr %u (Right Fork: %p  Left Fork: %p)\n"
		, pointer->position, pointer->right_fork, pointer->left_fork);
		pointer = pointer->left_philo;
	}
}
