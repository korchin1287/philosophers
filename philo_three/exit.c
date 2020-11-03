/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:00:51 by nofloren          #+#    #+#             */
/*   Updated: 2020/11/03 17:35:35 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		kill_all(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_filo)
	{
		kill(data->philo[i].pid, SIGINT);
		i++;
	}
	return (1);
}

int		str_error(int ret)
{
	if (ret == 1)
		ft_putstr_fd("Error: bad get time\n", 2);
	else if (ret == 2)
		ft_putstr_fd("Error: bad semaphore\n", 2);
	return (1);
}

int		exit_str(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	return (1);
}

int		clear_data(t_data *data)
{
	int i;

	i = 0;
	if (data->philo)
	{
		sem_unlink("name");
		sem_unlink("name2");
		free(data->philo);
	}
	return (1);
}
