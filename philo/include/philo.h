/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:22:12 by mait-elk          #+#    #+#             */
/*   Updated: 2024/02/27 18:29:30 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_session_data {
	size_t	start_time;
	int		time_to_sleep;
	int		num_of_philos;
	int		num_of_meals;
	int		time_to_die;
	int		time_to_eat;
}	t_session_data;

typedef struct	s_philo{
	t_session_data	*session_data;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		thread;
	size_t			last_meal_time;
	int				n_of_meals;
	int				id;
}	t_philo;

typedef struct s_session {
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printf_mutex;
	t_session_data	session_data;
}	t_session;

int			_nsx_session_init(t_session	*session, int ac, char **av);
void		_nsx_putstr_fd(char	*str, int fd);
void		_nsx_free_session(t_session *session);
size_t		_nsx_get_time();
void		_nsx_sleep(size_t ms);

void		_nsx_philo_think(t_philo *philo);
void		_nsx_philo_take_forks_eat(t_philo *philo);
void		_nsx_philo_sleep(t_philo *philo);

#endif
