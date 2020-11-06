/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:31:06 by nofloren          #+#    #+#             */
/*   Updated: 2020/11/06 14:55:27 by nofloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_philo
{
	pthread_t		id;
	int				index;
	int				done;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				must_eat_count;
	int				ret;
	size_t			time_to_die;
	struct s_data	*data;
	struct timeval	start_time;
	struct timeval	time_last_eat;
	struct timeval	now_time;
	pthread_mutex_t	*l_hand;
	pthread_mutex_t	*r_hand;
}					t_philo;

typedef struct		s_data
{
	int				dead;
	int				num_filo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	**forks;
	struct timeval	start_time;
}					t_data;

int					main(int argc, char **argv);
int					init(t_data *data, int argc, char **argv);
int					exit_str(char *str);
int					clear_data(t_data *data);
int					ft_atoi(const char *str);
int					ft_atoi(const char *str);
int					ft_sleep(long long need_time, struct timeval last_time);
int					ft_strlen(const char *str);
int					str_error(int ret);
int					print_status(t_philo *philo, int i);
void				*live(void *philo_v);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putchar_fd(char c, int fd);

#endif
