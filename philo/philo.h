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
# include <stdlib.h>

# define ERR_1 "Required arguments: number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define ERR_2 "Arguments can only be numeric\n"
# define ERR_3 "Arguments need to be >= 1\n"
# define ERR_4 "Arguments should be <= MAX_INT (2147483647)\n"
# define ERR_5 "Error malloc'ing data struct\n"
# define ERR_6 "Error creating data mutex\n"

# define ACT_1 " is eating\n"
# define ACT_2 " is taking a fork\n"
# define ACT_3 " is sleeping\n"
# define ACT_4 " is thinking\n"
# define ACT_5 " is full\n"
# define ACT_6 " is dead\n"

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	long	id;
	int		in_use;
	t_mtx	mtx;
}	t_fork;

typedef struct s_philos
{
	int			id;
	pthread_t	thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	long		time_last_meal;
	long		time_this_meal;
	long		times_ate;
	long		time_to_eat;
	long		time_to_sleep;
	long		time_to_die;
	long		number_of_eats;
	int			alive;
	int			full;
	t_mtx		mtx;
}	t_philos;

typedef struct s_data
{
	int			number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		started_sim_time;
	int			number_of_eats;
	int			ended_sim;
	t_mtx		mtx;
	t_fork		**forks;
	t_philos	**philos;
	pthread_t	ref;
}	t_data;

typedef enum e_ops
{
	CREATE,
	LOCK,
	UNLOCK,
	DESTROY,
	JOIN,
	DETACH
}	t_ops;

//parser.c
t_data		*parser(int argc, char **argv);

//forks.c
t_fork		**init_forks(t_data *data);
t_fork		**fork_err(t_data *data, int i);

//philos.c
t_philos	**init_philos(t_data *data);
t_philos	**philos_err(t_data *data, int i);
t_philos	**single_philo(t_data *data);
void		add_params_to_philo(t_data *data, t_philos *philo);
int			create_philos(t_data *data);

//philos2.c
void		eat(t_philos *philo);
void		_sleep(t_philos *philo);
void		think(t_philos *philo);
void		take_forks(t_philos *philo);
void		drop_forks(t_philos *philo);

//simulation.c
void		simulate(t_data *data);
void		*run(void *arg);
void		*ref(void *arg);
void		kill_all(t_data *data);
int			check_if_dead(t_data *data);

//simulation_utils.c
void		check_times_ate(t_philos *philo);
int			check_if_hungry(t_philos *philo);
int			has_right_fork(t_philos *philo);
int			check_if_all_full(t_data *data);

//safe_checks.c
int			get_id(t_philos *philo);
int			is_full(t_philos *philo);
int			is_alive(t_philos *philo);
int			get_time_to_sleep(t_philos *philo);

//time.c
long		now(void);
long		start(void);
long		ms_to_us(long ms);
void		smart_usleep(t_philos *philo, long us);

//threads.c
int			thread(pthread_t *thread, void *(*f)(void *),
				void *philo, t_ops op);

//writes.c
t_mtx		*write_lock(void);
void		_write(long time, t_philos *philo, char *str, int strlen);

//clean
void		clean(t_data *data);

//not_libft
int			ft_str_isdigit(char *str);
size_t		ft_strlen(const char *str);
int			ft_check_for_overflow(char *nb);
int			ft_atoi(const char *nptr);
void		ft_putnbr_fd(long n, int fd);

//really_not_libft
int			ft_isspace(char c);

#endif
