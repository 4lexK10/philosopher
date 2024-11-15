/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 02:28:09 by akloster          #+#    #+#             */
/*   Updated: 2024/11/05 18:54:37 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data 			data;

	if (ac != 5 && ac != 6)
		return (ft_error("Error: incorrect number of arguments"));
	memset(&data, 0, sizeof(t_data));
	if (parsing(av, &data) == EXIT_FAILURE)
		return (my_free(&data), EXIT_FAILURE);
	// printf("n_philo: %d\ndie: %d\neat: %d\nsleep: %d\n".n_philo.time_die.time_eat.time_sleep);
	if (alloc_threads(&data) == EXIT_FAILURE)
		return (my_free(&data), EXIT_FAILURE);
	if (init_philo(&data) == EXIT_FAILURE)
		return (my_free(&data), EXIT_FAILURE);
	my_free(&data);
	return (EXIT_SUCCESS);
}
