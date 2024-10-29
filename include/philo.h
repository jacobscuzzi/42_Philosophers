/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:17:36 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/10/29 03:37:10 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_dataset
{
	bool			limit;
	unsigned int	seats;
	unsigned int	forks;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_spleep;
	unsigned int	nbr_eat;
}	t_dataset;

typedef struct s_philo
{

} t_deep

bool	nbr_check(char *string);

int		ft_isdigit(int c);
int	ft_atoi(const char *str);


#endif
