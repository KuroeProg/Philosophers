#include "philo.h"
long	check_diff(struct timeval *s, struct timeval *e)
{
	return(e->tv_sec - s->tv_sec) * 1000000 + (e->tv_usec - s->tv_usec);
}

int	check_death(t_data *data, t_philo *philo)
{
	int		i;
	long	time_diff;
	struct timeval	current_time;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		gettimeofday(&current_time, NULL);
		time_diff = check_diff(&philo[i].last_meal, &current_time);
		if (time_diff > data->time_to_die * 1000)
		{
			printstatut(&philo[i], "died");
			data->simulation = 1;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	return (1);
}

int	monitoring(t_data *data, t_philo *philo)
{
	int	full_count;
	int	i;

	while (1)
	{
		i = 0;
		full_count = 0;
		if (!check_death(data, philo))
			return (1);
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->sim_mutex);
			if (philo[i].is_full)
				full_count++;
			pthread_mutex_unlock(&data->sim_mutex);
			i++;
		}
		if (full_count == data->num_philo)
		{
			data->simulation = 1;
			return (1);
		}
		usleep(1000);
	}
	return (0);
}
