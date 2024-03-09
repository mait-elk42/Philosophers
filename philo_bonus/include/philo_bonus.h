/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:30:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/09 14:00:29 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_data
{
	sem_t	*forks_lock;
	sem_t	*printf_lock;
	size_t	start_time;
	int		time_sleep;
	int		num_philos;
	int		num_meals;
	int		time_die;
	int		time_eat;
}	t_data;

typedef struct s_philo
{
	t_data	data;
	sem_t	*lock;
	pid_t	pid;
	size_t	last_meal_time;
	int		n_of_meals;
	int		id;
}	t_philo;

typedef struct s_session
{
	t_philo	*philos;
	t_data	data;
}	t_session;

int		nsx_init_data(t_data *data, int ac, char **av);
int		nsx_init_session(t_session *session);

void	nsx_put_philo_status(t_philo *philo, char *status);
int		nsx_valid_args(int ac, char **av);
void	nsx_sleep_ms(size_t ms);
int		nsx_atoi(char *num);
char	*nsx_itoa(int num);
size_t	nsx_get_time(void);

#endif