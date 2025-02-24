#include "philo.h"


void	p_sleep(t_philo *philo)
{
	printstatut(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	printstatut(philo, "is thinking");
	usleep(500);
}
void	*routine(void *arg)
{
	t_philo *p;
	
	p = (t_philo *)arg;
	if (p->data->simulation == 1)
		return (NULL);
	while (1)
	{
		take_forks(p);
		eat(p);
		put_forks(p);
		p_sleep(p);
		think(p);
		
		/* Apres que le philosophe ait mange on regarde s'il est repus*/
		if (p->data->num_to_eat > 0
			&& p->data->time_to_eat >= p->data->num_to_eat)
		{
			pthread_mutex_lock(&p->data->sim_mutex);
			p->is_full = 1;
			pthread_mutex_unlock(&p->data->sim_mutex);
			return (NULL);
		}
	}
	return (NULL);
}