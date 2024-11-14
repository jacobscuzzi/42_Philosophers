/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:17:36 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/11/14 22:06:02 by jbaumfal         ###   ########.fr       */
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
	pthread_mutex_t		times_eaten_lock;
	unsigned int		times_eaten;
	pthread_mutex_t		last_meal_lock;
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
	t_philo				*first_philo;
	struct timeval		time_start;
	pthread_t			death_check;
	pthread_mutex_t		game_over_lock;
	bool				game_over;
	pthread_mutex_t		print_lock;
}	t_dataset;

typedef struct s_fork
{
	pthread_mutex_t	lock;
}	t_fork;

# define NO_LOCK 0
# define LEFT_FORK 1
# define RIGHT_FORK 2
# define BOTH_FORKS 3

void			philo_dead(t_philo *philo);

int				init_forks(t_dataset *data);
bool			arg_check(int argc, char **argv);
t_dataset		*init_data(int argc, char **argv);
void			init_philo(t_philo *philo, t_dataset *data);
t_philo			*create_philos(t_dataset *data);

bool			nbr_check(char *string);
bool			ft_isdigit(int c);
unsigned int	ft_atou(const char *str);
void			print_philos(t_philo *philo);
unsigned int	get_ts(t_dataset *data);
void			kill_philo(t_philo *philo, int flag);

int				run_simulation(t_dataset *data);

int				philo_print(t_philo *philo, char *string);
int				thinking(t_philo *philo);
int				grab_forks(t_philo *philo);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);

int				philo_print(t_philo *philo, char *string);

bool			game_over_check(t_dataset *data);
void			livecheck(t_dataset *data);
bool			mealcheck(t_dataset *data);

#endif
