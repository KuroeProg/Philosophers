#ifndef PHILO_H
#define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	struct timeval start_time;
	pthread_mutex_t *fork;
	pthread_mutex_t sim_mutex;
	long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_to_eat;
	int		simulation; //1 == finished
}			t_data;

typedef struct s_philo
{
	int	id;
	struct timeval start_time;
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
int		init_mutex(t_data *data, t_philo *philo);
int		fork_to_philo(t_data *data, t_philo **philo);
int		start_init_philo(t_data *data, t_philo **philo);

/*
** utils
*/
long	ft_atol(char *str);
long	get_time_in_ms();
void	parsing(char **av);
void	return_error();
int		check_num(char *str);

/*
** Management
*/
void	*routine(void *arg);
int		take_forks(t_philo *philo);
void	put_forks(t_philo *philo);
int		eat(t_philo *philo);
int		monitoring(t_data *data, t_philo *philo);
int		check_death(t_data *data, t_philo *philo);
int		check_meals(t_philo **philo, t_data *data);

/*
** display
*/
void	printstatut(t_philo *philo, const char *str);

// int		create_thread();
// int		manage_thread();
// int		manage_mutex();


#endif