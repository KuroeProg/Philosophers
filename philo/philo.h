#ifndef PHILO_H
#define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_data
{
	struct timeval start_time;
	pthread_mutex_t *fork;
	long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_to_eat;
}			t_data;

typedef struct s_philo
{
	int	id;
	struct timeval last_meal;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data *data;
	pthread_t thread;
	pthread_mutex_t meal_mutex;
	int	meals_eaten;
	int	is_full;
} t_philo;

/*
** inits
*/
int		init_value(char **av, t_data *data);
int		init_philo(t_data *data, t_philo *philo);
int		init_mutex(t_data *data);
int		fork_to_philo(t_data *data, t_philo **philo);
int		start_init_philo(t_data *data, t_philo **philo);

/*
** utils
*/
long	ft_atol(char *str);

/*
** Management
*/
int		create_thread();
int		manage_thread();
int		manage_mutex();


#endif