#include "philo.h"
long	check_diff(struct timeval *s, struct timeval *e)
{
	return((e->tv_sec - s->tv_sec) * 1000) +
		((e->tv_usec - s->tv_usec) / 1000);
}

int check_death(t_data *data, t_philo *philo)
{
    int i;
    struct timeval current;
    long time_diff;

    i = 0;
    while (i < data->num_philo)
    {
        pthread_mutex_lock(&philo[i].meal_mutex);
        gettimeofday(&current, NULL);
        time_diff = ((current.tv_sec - philo[i].last_meal.tv_sec) * 1000) +
                   ((current.tv_usec - philo[i].last_meal.tv_usec) / 1000);

        if (time_diff > data->time_to_die)
        {
            pthread_mutex_lock(&data->sim_mutex);
            if (!data->simulation)
            {
                data->simulation = 1;
                time_diff = check_diff(&data->start_time, &current);
                printf("%ldms %d died\n", time_diff, philo[i].id);
            }
            pthread_mutex_unlock(&data->sim_mutex);
            pthread_mutex_unlock(&philo[i].meal_mutex);
            return (0);
        }
        pthread_mutex_unlock(&philo[i].meal_mutex);
        i++;
    }
    return (1);
}

int monitoring(t_data *data, t_philo *philo)
{
    while (!data->simulation)
    {
        if (!check_death(data, philo))
            return (0);
        usleep(100);
    }
    return (1);
}

// int monitoring(t_data *data, t_philo *philo)
// {
//     int i;
//     struct timeval current;
//     long time_diff;

//     while (!data->simulation)  
//     {
//         i = 0;
//         while (i < data->num_philo)
//         {
//             pthread_mutex_lock(&philo[i].meal_mutex);
//             gettimeofday(&current, NULL);
//             time_diff = check_diff(&philo[i].last_meal, &current);
            
//             if (time_diff > data->time_to_die)
//             {
//                 pthread_mutex_lock(&data->sim_mutex);
//                 if (!data->simulation)  // Vérifier si un autre philosophe n'est pas déjà mort
//                 {
//                     data->simulation = 1;
//                     printstatut(&philo[i], "died");
//                 }
//                 pthread_mutex_unlock(&data->sim_mutex);
//                 pthread_mutex_unlock(&philo[i].meal_mutex);
//                 return (0);
//             }
//             pthread_mutex_unlock(&philo[i].meal_mutex);
//             i++;
//         }
//         usleep(100);
//     }
//     return (1);
// }
// int	monitoring(t_data *data, t_philo *philo)
// {
// 	int	full_count;
// 	int	i;

// 	while (1)
// 	{
// 		i = 0;
// 		full_count = 0;
// 		if (!check_death(data, philo))
// 			return (1);
// 		while (i < data->num_philo)
// 		{
// 			pthread_mutex_lock(&data->sim_mutex);
// 			if (philo[i].is_full)
// 				full_count++;
// 			pthread_mutex_unlock(&data->sim_mutex);
// 			i++;
// 		}
// 		if (full_count == data->num_philo)
// 		{
// 			data->simulation = 1;
// 			return (1);
// 		}
// 		usleep(1000);
// 	}
// 	return (0);
// }
