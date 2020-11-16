#include "philosophers.h"

void			*check_dead(void *data_v)
{
	size_t			time;
	t_data			*data;
	struct timeval	now_time;

	data = (t_data*)data_v;
	while (1)
	{
		if ((gettimeofday(&now_time, NULL)) == -1)
			break ;
		usleep(50);
		time = (size_t)((now_time.tv_sec -
			data->philo[data->i].time_last_eat.tv_sec) * 1000 +
			(now_time.tv_usec - data->philo[data->i].time_last_eat.tv_usec)
			/ 1000);
		if (time > data->philo[data->i].time_to_die)
		{
			print_status(data, 4);
			data->dead = 1;
			exit(1);
		}
	}
	return ((void*)0);
}

static int		eating(t_data *data)
{
	if (sem_wait(data->sema) == -1)
		return (2);
	if (sem_wait(data->sema) == -1)
		return (2);
	if (print_status(data, 1) || print_status(data, 1))
		return (4);
	if (gettimeofday(&data->philo[data->i].time_last_eat, NULL) == -1)
		return (3);
	if (print_status(data, 2))
		return (4);
	if (gettimeofday(&data->philo[data->i].now_time, NULL) == -1)
		return (3);
	if (ft_sleep(data->philo[data->i].time_to_eat,
		data->philo[data->i].now_time))
		return (3);
	if (sem_post(data->sema) == -1)
		return (2);
	if (sem_post(data->sema) == -1)
		return (2);
	if (++(data->philo[data->i].eat_count) ==
		data->philo[data->i].must_eat_count)
		exit(69);
	return (0);
}

static int		sleeping(t_data *data)
{
	if (print_status(data, 3))
		return (4);
	if (gettimeofday(&data->philo[data->i].now_time, NULL) == -1)
		return (3);
	if (ft_sleep(data->philo[data->i].time_to_sleep,
		data->philo[data->i].now_time))
		return (3);
	return (0);
}

void			*live(void *data_v)
{
	pthread_t	id2;
	t_data		*data;

	data = (t_data*)data_v;
	if ((pthread_create(&id2, NULL, &check_dead, data)) != 0)
		exit(1);
	while (data->dead == 0)
	{
		if ((data->philo[data->i].ret = eating(data)))
			break ;
		if ((data->philo[data->i].ret = sleeping(data)))
			break ;
		if ((data->philo[data->i].ret = print_status(data, 5)))
			break ;
	}
	exit(1);
}
