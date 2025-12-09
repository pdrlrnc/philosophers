/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:32:12 by pedde-so          #+#    #+#             */
/*   Updated: 2025/11/20 11:32:14 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include "libft.h"

# define ERR_1 "Required arguments: number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_2 "Arguments can only be numeric\n"
# define ERR_3 "Arguments need to be >= 1\n"
# define ERR_4 "Arguments should be <= MAX_INT (2147483647)\n"
# define ERR_5 "Error malloc'ing data struct\n"
# define ERR_6 "Error creating data mutex\n"

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	long	id;
	t_mtx	mtx;
}	t_fork;

typedef struct s_referee
{
	int			id;
	t_mtx	mtx;
}	t_referee;

typedef struct s_philos
{
	int		id;
	pthread_t	thread;
	t_fork	*left_fork;
	t_fork	*right_fork;
	long	time_last_meal;
	long	time_this_meal;
	long	times_ate;
	t_mtx	mtx;
}	t_philos;

typedef struct s_data
{
	int			number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			number_of_eats;
	int			ended_sim;
	t_mtx		mtx;
	t_fork		**forks;
	t_philos	**philos;
	t_referee	**referees;
}	t_data;

typedef enum e_ops
{
	CREATE,
	LOCK,
	UNLOCK,
	DESTROY
}	t_ops;

//parser.c
t_data		*parser(int argc, char **argv);

//forks.c
t_fork		**init_forks(t_data *data);
t_fork		**fork_err(t_data *data, int i);

//mutexes.c
int			mutex(t_mtx mut, t_ops op);
t_mtx		write_lock(void);

//philos.c
t_philos	**init_philos(t_data *data);
t_philos	**philos_err(t_data *data, int i);
int			create_philos(t_data *data);

//simulation.c
int			ended_sim(t_data *data);
void		simulate(t_data *data);


//time.c
long		now(void);

#endif
