#include "philosophers.h"

void			*check_dead(void *philo_v)
{
	t_philo			*philo;
	struct timeval	now_time;
	size_t			time;

	philo = (t_philo*)philo_v;
	while (1)
	{
		if (gettimeofday(&now_time, NULL) == -1)
			break ;
		usleep(50);
		time = (size_t)((now_time.tv_sec - philo->time_last_eat.tv_sec) * 1000 +
			(now_time.tv_usec - philo->time_last_eat.tv_usec) / 1000);
		if (time > philo->time_to_die)
		{
			print_status(philo, 4);
			philo->data->dead = 1;
			philo->ret = 5;
			break ;
		}
	}
	return ((void*)0);
}

static int		eating(t_philo *philo)
{
	if (sem_wait(philo->data->sema) == -1)
		return (2);
	if (sem_wait(philo->data->sema) == -1)
		return (2);
	if (print_status(philo, 1) || print_status(philo, 1))
		return (4);
	if (gettimeofday(&philo->time_last_eat, NULL) == -1)
		return (3);
	if (print_status(philo, 2))
		return (4);
	if (gettimeofday(&philo->now_time, NULL) == -1)
		return (3);
	if (ft_sleep(philo->time_to_eat, philo->now_time))
		return (3);
	if (sem_post(philo->data->sema) == -1)
		return (2);
	if (sem_post(philo->data->sema) == -1)
		return (2);
	if (++(philo->eat_count) == philo->must_eat_count)
		philo->done = 1;
	return (philo->done);
}

static int		sleeping(t_philo *philo)
{
	if (print_status(philo, 3))
		return (4);
	if (gettimeofday(&philo->now_time, NULL) == -1)
		return (3);
	if (ft_sleep(philo->time_to_sleep, philo->now_time))
		return (3);
	return (0);
}

void			*live(void *philo_v)
{
	pthread_t	id2;
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	if ((pthread_create(&id2, NULL, &check_dead, philo)) != 0)
		return (NULL);
	while (philo->data->dead == 0)
	{
		if ((philo->ret = eating(philo)))
			break ;
		if ((philo->ret = sleeping(philo)))
			break ;
		if ((philo->ret = print_status(philo, 5)))
			break ;
	}
	return ((void*)0);
}
