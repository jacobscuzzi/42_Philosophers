/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:17:36 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/12 18:09:20 by jbaumfal         ###   ########.fr       */
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
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>

struct	s_dataset;

typedef struct s_philo
{
	unsigned int		position;
	pthread_t			thread;
	struct s_philo		*left_philo;
	struct s_fork		*left_fork;
	struct s_fork		*right_fork;
	struct s_philo		*right_philo;
	struct s_dataset	*data;
	unsigned int		times_eaten;
	unsigned int		last_meal;
}	t_philo;

typedef struct s_dataset
{
	bool			limit;
	unsigned int	seats;
	unsigned int	forks;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_spleep;
	unsigned int	eat_max;
	t_philo			*first_philo;
	struct timeval	time_start;
	pthread_t		death_check;
	bool			game_over;
}	t_dataset;

typedef struct s_fork
{
	bool	free;
	pthread_mutex_t	lock;
}	t_fork;

void			philos_full(t_dataset *data);
void			philo_dead(t_philo *philo);

bool			arg_check(int argc, char **argv);
t_dataset		*init_data(int argc, char **argv);
t_philo			*init_philos(t_dataset *data);
int				init_forks(t_dataset *data);

bool			nbr_check(char *string);
bool			ft_isdigit(int c);
unsigned int	ft_atou(const char *str);
void			print_philos(t_philo *philo);
unsigned int	get_ts(t_dataset *data);
void			kill_philo(t_philo *philo);

int				run_simulation(t_dataset *data);
void			livecheck(t_dataset *data);

int				thinking(t_philo *philo);
int				grab_forks(t_philo *philo);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
#endif
