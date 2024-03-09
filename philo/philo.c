/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:21:41 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/09 16:54:54 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*life_of_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		pthread_mutex_lock(philo->printf_mutex);
		if (*philo->someone_died)
			return (pthread_mutex_unlock(philo->printf_mutex), NULL);
		pthread_mutex_unlock(philo->printf_mutex);
		if (nsx_philo_take_forks_eat(philo))
			return (NULL);
		nsx_put_philo_status(philo, PHILO_SLEEP);
		nsx_sleep_ms(philo->cp_data.time_sleep, philo);
		nsx_put_philo_status(philo, PHILO_THINK);
	}
	return (NULL);
}

void	func_dieosf(t_session *session, size_t	mt, int i)
{
	pthread_mutex_lock(&session->printf_mutex);
	session->someone_died = 1;
	printf("%zu %d is died\n", mt, session->philos[i].id);
	pthread_mutex_unlock(&session->printf_mutex);
	pthread_mutex_unlock(&session->philos[i].meal_mutex);
	pthread_mutex_unlock(session->philos[i].left_fork);
}

static void	nsx_detector(t_session *session)
{
	size_t	meal_time;
	int		i;
	int		j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < session->data.num_philos)
		{
			pthread_mutex_lock(&session->philos[i].meal_mutex);
			meal_time = nsx_get_time() - session->philos[i].last_meal_time;
			j += (session->philos[i].n_of_meals == 0);
			if (j == session->data.num_philos)
				return ;
			if (session->philos[i].n_of_meals
				&& meal_time >= (size_t)session->data.time_die)
			{
				func_dieosf(session, meal_time, i);
				return ;
			}
			pthread_mutex_unlock(&session->philos[i].meal_mutex);
			i++;
		}
	}
}

static int	nsx_start_session(t_session *session)
{
	int	i;

	i = 0;
	while (i < session->data.num_philos)
	{
		if (pthread_create(&session->philos[i].thread,
				NULL, life_of_philo, &session->philos[i]))
			return (-1);
		if (i % 2 == 0)
			usleep(100);
		i++;
	}
	nsx_detector(session);
	i = 0;
	while (i < session->data.num_philos)
	{
		pthread_join(session->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_session	session;
	int			i;

	i = 1;
	if (ac != 5 && ac != 6)
		return (nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	while (i < ac)
	{
		if (nsx_atoi(av[i]) <= 0)
			return (nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
		i++;
	}
	nsx_init_data(&session.data, ac, av);
	if (nsx_init_mutexes(&session) == -1)
		return (nsx_free_session(&session),
			nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	if (nsx_init_philos(&session) == -1)
		return (nsx_free_session(&session),
			nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	if (nsx_start_session(&session) == -1)
		return (nsx_free_session(&session),
			nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	nsx_free_session(&session);
	return (0);
}
