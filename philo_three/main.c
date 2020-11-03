/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:56:12 by nofloren          #+#    #+#             */
/*   Updated: 2020/11/03 18:10:42 by nofloren         ###   ########.fr       */
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

static int	check_live(t_data *data)
{
	waitpid(-1, &data->status, 0);
	kill_all(data);
	clear_data(data);
	return (0);
}

static int	start_live(t_data *data)
{
	data->i = -1;
	if (gettimeofday(&(data->start_time), NULL) == -1)
		return (1);
	while (++(data->i) < data->num_filo)
	{
		data->philo[data->i].start_time = data->start_time;
		if (gettimeofday(&data->philo[data->i].time_last_eat, NULL) == -1)
			return (data->i);
		data->philo[data->i].pid = fork();
		if (data->philo[data->i].pid == 0)
		{
			live(data);
			exit (1);
		}
		else if (data->philo[data->i].pid < 0)
			return (1);
	}
			return (check_live(data));
}

int			main(int argc, char **argv)
{
	t_data	data;
	
	memset(&data, 0, sizeof(t_data));
	if (argc < 5 || argc > 6)
		return (exit_str("Error: bad argument\n"));
	if (init(&data, argc, argv))
	{
		return (clear_data(&data) &&
			exit_str("Error: bad argument or bad init\n"));
	}
	if (start_live(&data))
	{
		return (kill_all(&data) && clear_data(&data) &&
			exit_str("Error: bad live of philosophers\n"));
	}
//	check_live(&data);
	return (0);
}
