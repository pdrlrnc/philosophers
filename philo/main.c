/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:31:24 by pedde-so          #+#    #+#             */
/*   Updated: 2025/11/20 11:31:25 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ***************************************************************************/

#include "philo.h"

int	main(int argc, char **argv)
{
	if (pthread_mutex_init(write_lock(), NULL))
		return (write(STDERR_FILENO, "Error creating write mutex\n", 27), 1);
	if (!parser(argc, argv))
		return (1);
	while (!(*_data(NULL))->ended_sim)
	{
		simulate(*_data(NULL));
		usleep(500);
		return (1);
	}
	return (0);
}
