#include "philo.h"

long	ft_atol(char *str)
{
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	while (*str > 9 && *str < 13 || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str > '0' && *str < '9')
		result = result * 10 + (*str - '0');
	return (result * sign);
}
