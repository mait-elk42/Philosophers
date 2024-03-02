/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:21:41 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/02 23:17:21 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

ADD ANOTHER MUTEXES INSIDE PHILO STRUCT NAMED MUTEX_TIME_MEALS AND MUTEX_N_MEALS

static void	*life_of_philo(void *philo_ptr)
{
	t_philo	*philo;
	int		n_of_meals;

	philo = (t_philo *)philo_ptr;
	// if (philo->id % 2 == 0)
	// 	usleep(1000);
	n_of_meals = philo->n_of_meals;
	while (n_of_meals)
	{
		nsx_philo_think(philo);
		nsx_philo_take_forks_eat(philo);
		nsx_philo_sleep(philo);
		n_of_meals = philo->n_of_meals;
	}
	return (NULL);
}

static void	nsx_detector(t_session *session)
{
	int		i;
	int		j;
	size_t	meal_time;

	i = 0;
	j = 0;
	while (1)
	{
		pthread_mutex_lock(&session->printf_mutex);
		usleep(50);
		pthread_mutex_lock(&session->philos[i].meals_mutex);
		j += (session->philos[i].n_of_meals == 0);
		meal_time = nsx_get_time() - session->philos[i].last_meal_time;
		if (meal_time >= (size_t)session->data.time_die)
		{
			printf("%zu %d is died\n", meal_time, session->philos[i].id);
			pthread_mutex_destroy(&session->printf_mutex);
			return ;
		}
		if (j == session->data.num_philos)
			break ;
		pthread_mutex_unlock(&session->philos[i++].meals_mutex);
		i *= (i < session->data.num_philos);
		j *= (i < session->data.num_philos);
		pthread_mutex_unlock(&session->printf_mutex);
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
		if (pthread_detach(session->philos[i].thread))
			return (-1);
		i++;
		usleep(100);
	}
	nsx_detector(session);
	return (0);
}

int	main(int ac, char **av)
{
	t_session	session;

	session.forks = NULL;
	session.philos = NULL;
	if (nsx_session_init(&session, ac, av) == -1)
		return (nsx_free_session(&session),
			nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	if (nsx_start_session(&session) == -1)
		return (nsx_free_session(&session),
			nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	free(session.philos);
	free(session.forks);
	return (0);
}
