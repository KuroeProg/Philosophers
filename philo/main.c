/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiachet <cfiachet@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:31:05 by cfiachet          #+#    #+#             */
/*   Updated: 2025/02/23 12:38:22 by cfiachet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac < 6 || !init_value(av, &data) || !start_init_philo)
		return (0);
	if (!init_mutex(&data) || !fork_to_philo(&data, &philo))
		return (0);
		
	pthread_mutex_destroy(&philo->meal_mutex);
}   