/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _debug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:29:15 by pedde-so          #+#    #+#             */
/*   Updated: 2025/12/09 16:29:15 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#import "philo.h"

void	print_table(t_data *data)
{
	int	i;

	i = 0;
	while (data->philos[i])
	{
		write(STDOUT_FILENO, "philosopher (", 13);
		ft_putnbr_fd(data->philos[i]->id, STDOUT_FILENO);
		write(STDOUT_FILENO, ") has left fork (", 17);
		ft_putnbr_fd(data->philos[i]->left_fork->id, STDOUT_FILENO);
		write(STDOUT_FILENO, ") and right fork (", 18);
		ft_putnbr_fd(data->philos[i]->right_fork->id, STDOUT_FILENO);
		write(STDOUT_FILENO, ").\n", 3);
		i++;
	}
}

void	print_data_vars(t_data *data)
{
	write(STDOUT_FILENO, "number_of_philosophers: ", 24);
	ft_putnbr_fd(data->number_of_philosophers, STDOUT_FILENO);
	write(STDOUT_FILENO, " time_to_die: ", 14);
	ft_putnbr_fd(data->time_to_die, STDOUT_FILENO);
	write(STDOUT_FILENO, " time_to_eat: ", 14);
	ft_putnbr_fd(data->time_to_eat, STDOUT_FILENO);
	write(STDOUT_FILENO, " time_to_sleep: ", 16);
	ft_putnbr_fd(data->time_to_sleep, STDOUT_FILENO);
	write(STDOUT_FILENO, " number_of_eats: ", 17);
	ft_putnbr_fd(data->number_of_eats, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
}
