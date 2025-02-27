/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiachet <cfiachet@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:31:05 by cfiachet          #+#    #+#             */
/*   Updated: 2025/02/27 18:34:40 by cfiachet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	int		i;

	parsing(av + 1);
	if (ac < 5 || !init_value(av, &data) || !start_init_philo(&data, &philo))
		return (0);
	if (!init_mutex(&data, philo) || !fork_to_philo(&data, &philo))
		return (0);
	i = 0;
	if (!monitoring(&data, philo))
		exit(0);
	while (i < data.num_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	//free function
	if (philo)
	{
		i = 0;
		while (i < data.num_philo)
		{
			pthread_mutex_destroy(&philo[i].meal_mutex);
			pthread_mutex_destroy(&data.fork[i]);
			i++;
		}
		free(data.fork);
		free(philo);
	}
	pthread_mutex_destroy(&philo->meal_mutex);
	return (0);
}