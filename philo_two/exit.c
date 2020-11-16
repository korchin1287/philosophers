#include "philosophers.h"

int		str_error(int ret)
{
	if (ret == 3)
		ft_putstr_fd("Error: bad get time\n", 2);
	else if (ret == 2)
		ft_putstr_fd("Error: bad mutex or semaphore\n", 2);
	else if (ret == 4)
		ft_putstr_fd("Error: bad print\n", 2);
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
	if (data->philo)
	{
		sem_unlink("name");
		sem_unlink("name2");
		free(data->philo);
	}
	return (1);
}
