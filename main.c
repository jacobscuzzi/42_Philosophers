/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:15:19 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/10/29 00:51:35 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

bool	arg_check(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (false);

}
int	main(int argc, char **argv)
{

	if (!arg_check(argc, argv))
		return (EXIT_FAILURE);
}
