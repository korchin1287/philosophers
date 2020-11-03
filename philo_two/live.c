/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:29:39 by nofloren          #+#    #+#             */
/*   Updated: 2020/11/02 19:56:45 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		check_dead(t_philo *philo)
{
	size_t	time;

	if (gettimeofday(&philo->now_time, NULL) == -1)
		return (1);
	time = (size_t)(((philo->now_time.tv_sec - philo->time_last_eat.tv_sec)
		* 1000) + ((philo->now_time.tv_usec - philo->time_last_eat.tv_usec)
		/ 1000));
	if (time > philo->time_to_die)
	{
		print_status(philo, 4);
		return (1);
	}
	return (0);
}

static int		eating(t_philo *philo)
{
	if (sem_wait(philo->data->sema) == -1)
		return (2);
	if (sem_wait(philo->data->sema) == -1)
		return (2);
	if (print_status(philo, 1) || print_status(philo, 1))
		return (2);
	if (check_dead(philo))
		return (4);
	if (gettimeofday(&philo->time_last_eat, NULL) == -1)
		return (3);
	if (print_status(philo, 2))
		return (3);
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
		return (1);
	if (gettimeofday(&philo->now_time, NULL) == -1)
		return (1);
	if (ft_sleep(philo->time_to_sleep, philo->now_time))
		return (1);
	return (0);
}

void			*live(void *philo_v)
{
	t_philo *philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		if ((philo->ret = eating(philo)))
			break ;
		if (sleeping(philo))
			break ;
		if (print_status(philo, 5))
			break ;
	}
	return ((void*)0);
}
