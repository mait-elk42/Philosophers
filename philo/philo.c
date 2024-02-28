/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:21:41 by mait-elk          #+#    #+#             */
/*   Updated: 2024/02/28 19:23:06 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*life_of_philo(void *philo_ptr)
{
	t_philo	*philo;
	int		n_of_meals;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&philo->time_mutex);
	n_of_meals = philo->n_of_meals;
	pthread_mutex_unlock(&philo->time_mutex);
	while (n_of_meals)
	{
		_nsx_philo_think(philo);
		_nsx_philo_take_forks_eat(philo);
		_nsx_philo_sleep(philo);
		pthread_mutex_lock(&philo->time_mutex);
		n_of_meals = philo->n_of_meals;
		pthread_mutex_unlock(&philo->time_mutex);
	}
	return (NULL);
}

static void	_nsx_detector(t_session *session)
{
	int		i;
	int		j;
	size_t	meal_time;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < session->session_data.num_of_philos)
		{
			pthread_mutex_lock(&session->philos[i].time_mutex);
			j += (session->philos[i].n_of_meals == 0);
			meal_time = _nsx_get_time() - session->philos[i].last_meal_time;
			if (meal_time >= (size_t)session->session_data.time_to_die)
			{
				pthread_mutex_lock(&session->printf_mutex);
				printf("%zu %d is died\n", meal_time, session->philos[i].id);
				return ;
			}
			pthread_mutex_unlock(&session->philos[i].time_mutex);
			i++;
		}
		if (j == session->session_data.num_of_philos)
			break ;
	}
}

static int	_nsx_start_session(t_session *session)
{
	int	i;

	i = 0;
	while (i < session->session_data.num_of_philos)
	{
		if (pthread_create(&session->philos[i].thread,
				NULL, life_of_philo, &session->philos[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (i < session->session_data.num_of_philos)
	{
		if (pthread_detach(session->philos[i].thread))
			return (-1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_session	session;

	session.forks = NULL;
	session.philos = NULL;
	if (_nsx_session_init(&session, ac, av) == -1)
		return (_nsx_free_session(&session),
			_nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	if (_nsx_start_session(&session) == -1)
		return (_nsx_free_session(&session),
			_nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	_nsx_detector(&session);
	free(session.philos);
	free(session.forks);
	return (0);
}