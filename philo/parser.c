/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:53:09 by pedde-so          #+#    #+#             */
/*   Updated: 2025/11/20 13:53:11 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_numeric(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_str_isdigit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_if_pos(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (*argv[i] == '-' || (*argv[i] == '0' && ft_strlen(argv[i]) == 1))
			return (0);
		i++;
	}
	return (1);
}

static int	check_if_overflow(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_check_for_overflow(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	atoi_input(t_data *data, char **argv)
{	
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_eats = 0;
	if (argv[5])
		data->number_of_eats = ft_atoi(argv[5]);
}

t_data	*parser(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (write(STDERR_FILENO, "Required arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 125), NULL);
	if (!check_if_numeric(argv))
		return (write(STDERR_FILENO, "Arguments can only be numeric\n", 30), NULL);
	if (!check_if_pos(argv))
		return (write(STDERR_FILENO, "Arguments need to be >= 1\n", 26), NULL);
	if (!check_if_overflow(argv))
		return (write(STDERR_FILENO, "Arguments should be <= MAX_INT (2147483647)\n", 44), NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(STDERR_FILENO, "Error malloc'ing data struct\n", 29), NULL);
	if (mutex(data->mtx, CREATE))
	{
		write(STDERR_FILENO, "Error creating data mutex\n", 26);
		return (free(data), NULL);
	}
	data->ended_sim = 0;
	atoi_input(data, argv);
	return (data);
}
