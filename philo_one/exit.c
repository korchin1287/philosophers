/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:00:51 by nofloren          #+#    #+#             */
/*   Updated: 2020/10/31 18:34:46 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		str_error(int ret)
{
	if (ret == 1)
		ft_putstr_fd("Error: bad get time\n", 2);
	else if (ret == 2)
		ft_putstr_fd("Error: bad mutex\n", 2);
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
		while (i < data->num_filo)
		{
			pthread_mutex_destroy(data->forks[i]);
			free(data->forks[i]);
			i++;
		}
		free(data->philo);
	}
	return (1);
}
