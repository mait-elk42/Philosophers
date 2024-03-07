/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:22:12 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/07 23:19:49 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_THINK "is thinking"
# define PHILO_EAT "is eating"
# define PHILO_SLEEP "is sleep"
# define PHILO_TAKEN_A_FORK "has taken a fork"

typedef struct s_data
{
	size_t	start_time;
	int		time_sleep;
	int		num_philos;
	int		num_meals;
	int		time_die;
	int		time_eat;
}	t_data;

typedef struct s_philo
{
	t_data			cp_data;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				*someone_died;
	pthread_t		thread;
	size_t			last_meal_time;
	int				n_of_meals;
	int				id;
}	t_philo;

typedef struct s_session
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_mutex;
	int				someone_died;
	t_data			data;
}	t_session;

void		nsx_init_data(t_data *data, int ac, char **av);
int			nsx_init_philos(t_session *session);
int			nsx_init_mutexes(t_session *session);

void		nsx_putstr_fd(char	*str, int fd);
void		nsx_free_session(t_session *session);
size_t		nsx_get_time(void);
void		nsx_sleep_ms(size_t ms);

int			nsx_philo_think(t_philo *philo);
int			nsx_philo_take_forks_eat(t_philo *philo);
int			nsx_philo_sleep(t_philo *philo);

int			nsx_atoi(char *num);

#endif
