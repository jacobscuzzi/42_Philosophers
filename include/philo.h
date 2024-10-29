/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:17:36 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/10/29 18:03:49 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>



typedef struct s_philo
{
	unsigned int	position;
	struct s_philo	*left_philo;
	struct s_fork	*left_fork;
	struct s_fork	*right_fork;
	struct s_philo	*right_philo;

}	t_philo;

typedef struct s_dataset
{
	bool			limit;
	unsigned int	seats;
	unsigned int	forks;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_spleep;
	unsigned int	nbr_eat;
	t_philo			*first_philo;
}	t_dataset;

typedef struct s_fork
{
	bool	free;
}	t_fork;

bool			nbr_check(char *string);

bool			ft_isdigit(int c);
int unsigned	ft_atou(const char *str);

void			print_philos(t_philo *philo);

#endif
