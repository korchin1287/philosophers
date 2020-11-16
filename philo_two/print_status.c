#include "philosophers.h"

void	print_status_help(int i)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;

	str1 = " has taken a fork\n";
	str2 = " is eating\n";
	str3 = " is sleeping\n";
	str4 = " dead\n";
	if (i == 1)
		write(1, str1, 19);
	else if (i == 2)
		write(1, str2, 12);
	else if (i == 3)
		write(1, str3, 14);
	else if (i == 4)
		write(1, str4, 7);
	else
		write(1, " is thinking\n", 14);
}

int		print_status(t_philo *philo, int i)
{
	size_t	time;

	if (sem_wait(philo->data->sema2))
		return (2);
	if (philo->data->dead)
		return (1);
	if (gettimeofday(&philo->now_time, NULL) == -1)
		return (2);
	time = (size_t)(((philo->now_time.tv_sec - philo->start_time.tv_sec) *
		1000) + ((philo->now_time.tv_usec - philo->start_time.tv_usec) / 1000));
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->index, 1);
	print_status_help(i);
	if (sem_post(philo->data->sema2))
		return (2);
	return (0);
}
