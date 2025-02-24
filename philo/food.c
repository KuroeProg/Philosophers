#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printstatut(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	printstatut(philo, "has taken a fork");
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->meal_mutex);
	printstatut(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	if (philo->data->num_to_eat > 0)
		philo->meals_eaten++;
}