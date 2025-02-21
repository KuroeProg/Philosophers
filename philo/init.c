#include "philo.h"

void	init_value(char **av, t_data *data)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	data->start_time = now;
	data->num_philo = ft_atol(*av[1]);
	data->time_to_die = ft_atol(*av[2]);
	data->time_to_eat = ft_atol(*av[3]);
	data->time_to_sleep = ft_atol(*av[4]);

}

int	init_philo(t_data *data, t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	philo->id = 0;
	philo->last_meal = now;
	philo->left_fork = NULL;
	philo->right_fork = NULL;
	philo->data = data;
	philo->thread = NULL;
	if (pthread_mutex_init(&philo->meal_mutex, NULL))
	{
		write(2, "Mutex initialization failed\n", 29);
		return (1);
	}
	philo->meals_eaten = 0;
	philo->is_full = 0;
	return (0);
}
