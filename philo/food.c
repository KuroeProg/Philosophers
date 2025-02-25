#include "philo.h"

int take_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->sim_mutex);
    if (philo->data->simulation)
    {
        pthread_mutex_unlock(&philo->data->sim_mutex);
        return (0);
    }
    pthread_mutex_unlock(&philo->data->sim_mutex);
    if (philo->data->num_philo == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        printstatut(philo, "has taken a fork");
        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return (0);
    }
    if (philo->id % 2)
    {
        pthread_mutex_lock(philo->left_fork);
        printstatut(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        printstatut(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        printstatut(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        printstatut(philo, "has taken a fork");
    }
    return (1);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_mutex);
    if (philo->data->simulation)
    {
        pthread_mutex_unlock(&philo->meal_mutex);
        return (0);
    }
    gettimeofday(&philo->last_meal, NULL);
    printstatut(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    return (1);
}