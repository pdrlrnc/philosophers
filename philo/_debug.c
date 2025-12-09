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
		write(STDOUT_FILENO, "). has also a referee (", 23);
		ft_putnbr_fd(data->referees[i]->id, STDOUT_FILENO);
		write(STDOUT_FILENO, ").\n", 3);
		i++;
	}
}
