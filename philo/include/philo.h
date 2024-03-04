/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:22:12 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/03 22:59:28 by mait-elk         ###   ########.fr       */
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
	int		time_sleep;
	size_t	start_time;
	int		num_philos;
	int		num_meals;
	int		time_die;
	int		time_eat;
}	t_data;

typedef struct s_philo
{
	t_data			cp_data;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	n_meals_mutex;
	pthread_mutex_t	last_meal_time_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
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
	t_data			data;
}	t_session;

int			nsx_session_check_args(t_session	*session, int ac, char **av);

void		nsx_putstr_fd(char	*str, int fd);
void		nsx_free_session(t_session *session);
size_t		nsx_get_time(void);
void		nsx_sleep_ms(size_t ms);

void		nsx_philo_think(t_philo *philo);
void		nsx_philo_take_forks_eat(t_philo *philo);
void		nsx_philo_sleep(t_philo *philo);

#endif
