#include "philosophers.h"

static int	change_time(struct timeval tv)
{
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int			ft_sleep(long long need_time, struct timeval last_time)
{
	struct timeval	now_time;
	int				time;

	time = change_time(last_time) + (long long)need_time;
	if (gettimeofday(&now_time, NULL) == -1)
		return (1);
	while ((change_time(now_time) <= time))
	{
		if (usleep(50) == -1)
			return (1);
		if (gettimeofday(&now_time, NULL) == -1)
			return (1);
	}
	return (0);
}

static int	start_live(t_data *data)
{
	int i;

	i = 0;
	if (gettimeofday(&(data->start_time), NULL) == -1)
		return (1);
	while (i < data->num_filo)
	{
		data->philo[i].start_time = data->start_time;
		if (gettimeofday(&data->philo[i].time_last_eat, NULL) == -1)
			return (1);
		if ((pthread_create(&data->philo[i].id, NULL, &live, &data->philo[i]))
			!= 0)
			return (1);
		i++;
		usleep(30);
	}
	return (0);
}

static int	check_live(t_data *data)
{
	int	i;
	int count;

	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->num_filo)
		{
			if (data->philo[i].done)
				count++;
			if (data->philo[i].ret > 1)
				return (clear_data(data) && str_error(data->philo[i].ret));
			i++;
		}
		if (count == data->num_filo)
			return (clear_data(data));
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (exit_str("Error: bad argument\n"));
	if (init(&data, argc, argv))
	{
		return (clear_data(&data) &&
			exit_str("Error: bad argument or bad init\n"));
	}
	if (start_live(&data))
	{
		return (clear_data(&data) &&
			exit_str("Error: bad live of philosophers\n"));
	}
	check_live(&data);
	return (0);
}
