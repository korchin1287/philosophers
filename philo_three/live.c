/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:29:39 by nofloren          #+#    #+#             */
/*   Updated: 2020/11/03 18:07:07 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		check_dead(t_data *data)
{
	size_t	time;

	if (gettimeofday(&data->philo[data->i].now_time, NULL) == -1)
		return (1);
	time = (size_t)(((data->philo[data->i].now_time.tv_sec - data->philo[data->i].time_last_eat.tv_sec)
		* 1000) + ((data->philo[data->i].now_time.tv_usec - data->philo[data->i].time_last_eat.tv_usec)
		/ 1000));
	if (time > data->philo[data->i].time_to_die)
	{
		print_status(data, 4);
		return (1);
	}
	return (0);
}

static int		eating(t_data *data)
{
	if (sem_wait(data->sema) == -1)
		return (2);
	if (sem_wait(data->sema) == -1)
		return (2);
	if (print_status(data, 1) || print_status(data, 1))
		return (2);
	if (check_dead(data))
		return (4);
	if (gettimeofday(&data->philo[data->i].time_last_eat, NULL) == -1)
		return (3);
	if (print_status(data, 2))
		return (3);
	if (gettimeofday(&data->philo[data->i].now_time, NULL) == -1)
		return (3);
	if (ft_sleep(data->philo[data->i].time_to_eat, data->philo[data->i].now_time))
		return (3);
	if (sem_post(data->sema) == -1)
		return (2);
	if (sem_post(data->sema) == -1)
		return (2);
	data->philo[data->i].eat_count++;
	if ((data->philo[data->i].eat_count) == data->philo[data->i].must_eat_count)
		exit(1);
	return (0);
}

static int		sleeping(t_data *data)
{
	if (print_status(data, 3))
		return (1);
	if (gettimeofday(&data->philo[data->i].now_time, NULL) == -1)
		return (1);
	if (ft_sleep(data->philo[data->i].time_to_sleep, data->philo[data->i].now_time))
		return (1);
	return (0);
}

void			*live(void *data_v)
{
	t_data *data;

	data = (t_data*)data_v;
	while (1)
	{
		if ((data->philo[data->i].ret = eating(data)))
			break ;
		if (sleeping(data))
			break ; 
		if (print_status(data, 5))
			break ;
	}
	//return ((void*)0);
	exit(0);
}
