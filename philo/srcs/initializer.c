/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:51:06 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/03 22:58:45 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	nsx_atoi(char *num)
{
	long	r;
	int		sign;

	r = 0;
	sign = 1;
	while ((*num >= 9 && *num <= 13) || (*num == ' '))
		num++;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
			sign = -1;
		num++;
	}
	while (*num && (*num >= '0' && *num <= '9'))
	{
		r = (r * 10) + (*num - 48);
		if ((sign == 1 && r > 2147483647) || (sign == -1 && r > 2147483648))
			return (-1);
		num++;
	}
	return (sign * r);
}

static int	nsx_session_init_philos(t_session *session)
{
	t_data			data;
	int				i;

	i = 0;
	data = session->data;
	session->data.start_time = nsx_get_time();
	while (i < session->data.num_philos)
	{
		session->philos[i].id = i + 1;
		session->philos[i].n_of_meals = session->data.num_meals;
		session->philos[i].cp_data = session->data;
		session->philos[i].last_meal_time = session->data.start_time;
		session->philos[i].printf_mutex = &session->printf_mutex;
		if (pthread_mutex_init(&session->philos[i].last_meal_time_mutex, NULL))
			return (-1);
		if (pthread_mutex_init(&session->philos[i].n_meals_mutex, NULL))
			return (-1);
		if (i == 0)
			session->philos[i].left_fork = &session->forks[data.num_philos - 1];
		else
			session->philos[i].left_fork = &session->forks[i - 1];
		session->philos[i].right_fork = &session->forks[i];
		i++;
	}
	return (0);
}

static int	nsx_session_init_mutexes(t_session *session)
{
	t_data			s_data;
	int				i;

	i = 0;
	s_data = session->data;
	if (pthread_mutex_init(&session->printf_mutex, NULL))
		return (-1);
	while (i < s_data.num_philos)
	{
		if (pthread_mutex_init(&session->forks[i], NULL))
		{
			while (i)
				pthread_mutex_destroy(&session->forks[i--]);
			return (-1);
		}
		i++;
	}
	return (nsx_session_init_philos(session));
}

int	nsx_session_check_args(t_session	*session, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (-1);
	session->data.num_philos = nsx_atoi(av[1]);
	session->data.time_die = nsx_atoi(av[2]);
	session->data.time_eat = nsx_atoi(av[3]);
	session->data.time_sleep = nsx_atoi(av[4]);
	if (session->data.num_philos <= 0
		|| session->data.time_die <= 0
		|| session->data.time_eat <= 0
		|| session->data.time_sleep <= 0)
		return (-1);
	session->data.num_meals = -1;
	if (ac == 6)
	{
		session->data.num_meals = nsx_atoi(av[5]);
		if (session->data.num_meals <= 0)
			return (-1);
	}
	session->philos = malloc(sizeof(t_philo) * session->data.num_philos);
	if (!session->philos)
		return (-1);
	session->forks = malloc(sizeof(pthread_mutex_t) * session->data.num_philos);
	if (!session->forks)
		return (-1);
	return (nsx_session_init_mutexes(session));
}
