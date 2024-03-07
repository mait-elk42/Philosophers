/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:51:06 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/07 22:38:42 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	nsx_init_philos(t_session *session)
{
	int				i;

	session->philos = malloc(sizeof(t_philo) * session->data.num_philos);
	if (session->philos == NULL)
		return (-1);
	session->data.start_time = nsx_get_time();
	session->someone_died = 0;
	i = 0;
	while (i < session->data.num_philos)
	{
		session->philos[i].id = i + 1;
		session->philos[i].n_of_meals = session->data.num_meals;
		session->philos[i].cp_data = session->data;
		session->philos[i].last_meal_time = session->data.start_time;
		session->philos[i].someone_died = &session->someone_died;
		session->philos[i].printf_mutex = &session->printf_mutex;
		if (pthread_mutex_init(&session->philos[i].meal_mutex, NULL))
			return (-1);
		if (i == 0)
			session->philos[i].left_fork = &session->forks[session->data.num_philos - 1];
		else
			session->philos[i].left_fork = &session->forks[i - 1];
		session->philos[i].right_fork = &session->forks[i];
		i++;
	}
	return (0);
}

int	nsx_init_mutexes(t_session *session)
{
	int	i;

	i = 0;
	session->forks = malloc(sizeof(pthread_mutex_t) * session->data.num_philos);
	if (session->forks == NULL)
		return (-1);
	if (pthread_mutex_init(&session->printf_mutex, NULL))
		return (-1);
	while (i < session->data.num_philos)
	{
		if (pthread_mutex_init(&session->forks[i], NULL))
			return (-1);
		i++;
	}
	return (0);
}

void	nsx_init_data(t_data *data, int ac, char **av)
{
	data->num_philos = nsx_atoi(av[1]);
	data->time_die = nsx_atoi(av[2]);
	data->time_eat = nsx_atoi(av[3]);
	data->time_sleep = nsx_atoi(av[4]);
	data->num_meals = -1;
	if (ac == 6)
		data->num_meals = nsx_atoi(av[5]);
}
