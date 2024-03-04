/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:30:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/04 16:59:30 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int		time_sleep;
	int		num_philos;
	int		num_meals;
	int		time_die;
	int		time_eat;
}	t_data;

typedef struct s_philo
{
	pid_t	pid;
}	t_philo;


typedef struct s_session
{
	t_data	data;
	t_philo	*philo;
}	t_session;

void	nsx_init_data(t_session *session, int ac, char **av);
int		nsx_valid_args(int ac, char **av);
int		nsx_atoi(char *num);
int		nsx_put_error();

#endif