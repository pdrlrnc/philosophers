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

t_data	*parser(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (write(STDERR_FILENO, "Required arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 125), NULL);
	if (!check_if_numeric(argv))
		return (write(STDERR_FILENO, "Arguments can only be numeric\n", 30), NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->number_of_philosophers = check_nb(argv[1]);
	data->time_to_die = check_nb(argv[2]);
	data->time_to_eat = check_nb(argv[3]);
	data->time_to_sleep = check_nb(argv[4]);
	data->number_of_eats = -3;
	if (argv[5])
		data->number_of_eats = check_nb(argv[5]);
	return (final_data_check(data));
}

int	check_if_numeric(char **argv)
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

int	check_nb(char *nb_str)
{
	if (*nb_str == '-' || (*nb_str == '0' && ft_strlen(nb_str) == 1))
		return (-1);
	if (ft_check_for_overflow(nb_str))
		return (-2);
	return (ft_atoi(nb_str));
}

t_data	*final_data_check(t_data *data)
{
	if (data->number_of_philosophers == -1 || data->time_to_die == -1 
		|| data->time_to_eat == -1 || data->time_to_sleep == -1 
		|| data->number_of_eats == -1)
	{
		write(STDERR_FILENO, "Arguments should be >= 1\n", 25);
		free(data);
		data = NULL;
	}
	else if (data->number_of_philosophers == -2 || data->time_to_die == -2 
		|| data->time_to_eat == -2 || data->time_to_sleep == -2 
		|| data->number_of_eats == -2)
	{
		write(STDERR_FILENO, "Arguments should be <= MAX_INT (2147483647)\n", 44);
		free(data);
		data = NULL;
	}
	return (data);
}
