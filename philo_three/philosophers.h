/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofloren <nofloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:31:06 by nofloren          #+#    #+#             */
/*   Updated: 2020/11/01 16:17:55 by nofloren         ###   ########.fr       */
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
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct		s_philo
{
	pid_t			pid;
	pid_t			wpid;
	int				index;
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
}					t_philo;

typedef struct		s_data
{
	int				num_filo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				status;
	t_philo			*philo;
	sem_t			*sema;
	sem_t			*sema2;
	struct timeval	start_time;
}					t_data;

int					main(int argc, char **argv);
int					init(t_data *data, int argc, char **argv);
int					exit_str(char *str);
int					kill_all(t_data *data);
int					clear_data(t_data *data);
int					ft_atoi(const char *str);
int					ft_atoi(const char *str);
int					ft_sleep(long long need_time, struct timeval last_time);
int					ft_strlen(const char *str);
int					str_error(int ret);
void				*live(void *philo_v);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putchar_fd(char c, int fd);
void				print_status(t_philo *philo, int i);

#endif