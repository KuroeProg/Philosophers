#include "philo.h"


void	p_sleep(t_philo *philo)
{
	printstatut(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printstatut(philo, "is thinking");
}

void *routine(void *arg)
{
    t_philo *p;
    
    p = (t_philo *)arg;
    gettimeofday(&p->last_meal, NULL);
    if (p->id % 2)
        usleep(1000);
    while (!p->data->simulation)
    {
        if (!take_forks(p))
            break;
        if (!eat(p))
            break;
        put_forks(p);
        pthread_mutex_lock(&p->meal_mutex);
        if (p->data->num_to_eat > 0 && p->meals_eaten >= p->data->num_to_eat)
        {
            if (check_meals(&p, p->data) == 1)
            {
                printf("all meals eaten");
                exit(0);
                pthread_mutex_unlock(&p->meal_mutex);
            }
        }
    	pthread_mutex_unlock(&p->meal_mutex);
    	if (p->data->simulation)
    	    break;
    	p_sleep(p);
    	think(p);
    }
    return (NULL);
}