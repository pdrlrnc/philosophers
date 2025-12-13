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
	t_data	*data;

	data = parser(argc, argv);
	if (!data)
		return (1);
	if (pthread_mutex_init(write_lock(), NULL))
		return (write(STDERR_FILENO, "Error creating write mutex\n", 27), 1);
	if (!init_forks(data))
		return (write(STDERR_FILENO, "Error creating forks\n", 21), 1);
	if (!init_philos(data))
		return (write(STDERR_FILENO, "Error creating philosophers\n", 28), 1);
	simulate(data);
	return (0);
}
