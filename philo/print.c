#include "philo.h"

void	printstatut(t_philo *philo, const char *str)
{
    long	current_time;
    struct timeval	now;

    pthread_mutex_lock(&philo->data->sim_mutex);
    if (philo->data->simulation == 1)
    {
        pthread_mutex_unlock(&philo->data->sim_mutex);
        return;
    }
    gettimeofday(&now, NULL);
    current_time = (now.tv_sec - philo->data->start_time.tv_sec) * 1000 + 
                   (now.tv_usec - philo->data->start_time.tv_usec) / 1000;
    printf("%ldms %d %s\n", current_time, philo->id, str);
    pthread_mutex_unlock(&philo->data->sim_mutex);
}
