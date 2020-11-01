/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:56:12 by nofloren          #+#    #+#             */
/*   Updated: 2020/11/01 18:03:11 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (usleep(100) == -1)
			return (1);
		if (gettimeofday(&now_time, NULL) == -1)
			return (1);
	}
	return (0);
}

static int	start_live(t_data *data)
{
	int		i;

	i = 0;
	if (gettimeofday(&(data->start_time), NULL) == -1)
		return (1);
	while (i < data->num_filo)
	{
		data->philo[i].start_time = data->start_time;
		if (gettimeofday(&data->philo[i].time_last_eat, NULL) == -1)
			return (1);
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
			live(&data->philo[i]);
		if (data->philo[i].pid < 0)
			kill_all(data);
		i++;
	}
	
	return (0);
}

static int	check_live(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->num_filo)
		{
			if (data->philo[i].wpid == waitpid(data->philo[i].pid, &data->status, WUNTRACED))
				return (kill_all(data));
			i++;
		}
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
	if (check_live(&data))
		return (clear_data(&data));
	return (0);
}
