/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:51:06 by mait-elk          #+#    #+#             */
/*   Updated: 2024/02/28 18:22:58 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	_nsx_atoi(char *num)
{
	long	r;
	int		sign;

	r = 0;
	sign = 1;
	while ((*num >= 9 && *num <= 13) || *num == ' ')
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

static int	_nsx_session_init3(t_session *session)
{
	t_session_data	s_data;
	int				i;

	i = 0;
	s_data = session->session_data;
	session->session_data.start_time = _nsx_get_time();
	while (i < session->session_data.num_of_philos)
	{
		session->philos[i].id = i+1;
		session->philos[i].n_of_meals = session->session_data.num_of_meals;
		session->philos[i].session_data = &session->session_data;
		session->philos[i].last_meal_time = session->session_data.start_time;
		session->philos[i].printf_mutex = &session->printf_mutex;
		if (pthread_mutex_init(&session->philos[i].time_mutex, NULL))
			return (-1);
		if (i == 0)
			session->philos[i].left_fork = &session->forks[s_data.num_of_philos - 1];
		else
			session->philos[i].left_fork = &session->forks[i - 1];
		session->philos[i].right_fork = &session->forks[i];
		i++;
	}
	return (0);
}

static int	_nsx_session_init2(t_session *session)
{
	t_session_data	s_data;
	int				i;

	i = 0;
	s_data = session->session_data;
	if (pthread_mutex_init(&session->printf_mutex, NULL))
		return (-1);
	while (i < s_data.num_of_philos)
	{
		if (pthread_mutex_init(&session->forks[i], NULL))
		{
			while (i)
				pthread_mutex_destroy(&session->forks[i--]);
			return (-1);
		}
		i++;
	}
	return (_nsx_session_init3(session));
}

int	_nsx_session_init(t_session	*session, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (-1);
	session->session_data.num_of_philos = _nsx_atoi(av[1]);
	session->session_data.time_to_die = _nsx_atoi(av[2]);
	session->session_data.time_to_eat = _nsx_atoi(av[3]);
	session->session_data.time_to_sleep = _nsx_atoi(av[4]);
	if (session->session_data.num_of_philos <= 0
		|| session->session_data.time_to_die <= 0
		|| session->session_data.time_to_eat <= 0
		|| session->session_data.time_to_sleep <= 0)
			return (-1);
	session->session_data.num_of_meals = -1;
	if (ac == 6)
	{
		session->session_data.num_of_meals = _nsx_atoi(av[5]);
		if (session->session_data.num_of_meals <= 0)
			return (-1);
	}
	session->philos = malloc(sizeof(t_philo) * session->session_data.num_of_philos);
	if (!session->philos)
		return (-1);
	session->forks = malloc(sizeof(pthread_mutex_t) * session->session_data.num_of_philos);
	if (!session->forks)
		return (-1);
	return (_nsx_session_init2(session));
}
