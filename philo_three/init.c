#include "philosophers.h"

static int	init_data(t_data *data, char **argv)
{
	if ((data->num_filo = ft_atoi(argv[1])) < 2)
		return (1);
	if ((data->time_to_die = ft_atoi(argv[2])) < 0)
		return (1);
	if ((data->time_to_eat = ft_atoi(argv[3])) < 0)
		return (1);
	if ((data->time_to_sleep = ft_atoi(argv[4])) < 0)
		return (1);
	data->must_eat_count = -1;
	data->dead = 0;
	return (0);
}

static void	init_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_filo)
	{
		data->philo[i].done = 0;
		data->philo[i].index = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].ret = 0;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].must_eat_count = data->must_eat_count;
		i++;
	}
}

int			init(t_data *data, int argc, char **argv)
{
	if (init_data(data, argv))
		return (1);
	if (argc == 6)
	{
		data->must_eat_count = ft_atoi(argv[5]);
		if (data->must_eat_count == 0)
			return (1);
	}
	if (data->must_eat_count == -1)
		data->must_eat_count = 0;
	data->philo = NULL;
	if (!(data->philo = (t_philo*)malloc(sizeof(t_philo) * data->num_filo)))
		return (2);
	init_philos(data);
	sem_unlink("name");
	data->sema = sem_open("name", O_CREAT, 0666, data->num_filo);
	if (data->sema == SEM_FAILED)
		return (2);
	sem_unlink("name2");
	data->sema2 = sem_open("name2", O_CREAT, 0666, 1);
	if (data->sema2 == SEM_FAILED)
		return (2);
	return (0);
}
