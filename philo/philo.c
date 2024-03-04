/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:21:41 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/03 23:13:50 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*life_of_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	while (1)
	{
		if (philo->n_of_meals == 0)
			return (NULL);
		nsx_philo_think(philo);
		nsx_philo_take_forks_eat(philo);
		nsx_philo_sleep(philo);
		pthread_mutex_lock(&philo->n_meals_mutex);
		pthread_mutex_unlock(&philo->n_meals_mutex);
	}
	return (NULL);
}

static int	someone_died(t_session *session, int i)
{
	size_t	meal_time;

	pthread_mutex_lock(&session->philos[i].last_meal_time_mutex);
	meal_time = nsx_get_time() - session->philos[i].last_meal_time;
	if (session->philos[i].n_of_meals
		&& meal_time >= (size_t)session->data.time_die)
	{
		pthread_mutex_lock(&session->printf_mutex);
		printf("%zu %d is died\n", meal_time, session->philos[i].id);
		nsx_sleep_ms(10);
		return (1);
	}
	pthread_mutex_unlock(&session->philos[i++].last_meal_time_mutex);
	return (0);
}

static void	nsx_detector(t_session *session)
{
	int		i;
	int		j;

	while (1)
	{
		i = 0;
		j = 0;
		while (i < session->data.num_philos)
		{
			pthread_mutex_lock(&session->philos[i].n_meals_mutex);
			j += (session->philos[i].n_of_meals == 0);
			pthread_mutex_unlock(&session->philos[i].n_meals_mutex);
			if (someone_died(session, i))
				return ;
			i++;
		}
		if (j == session->data.num_philos)
			return ;
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
		usleep(10);
		i++;
	}
	nsx_detector(session);
	return (0);
}

int	main(int ac, char **av)
{
	t_session	session;

	session.forks = NULL;
	session.philos = NULL;
	if (nsx_session_check_args(&session, ac, av) == -1)
		return (nsx_free_session(&session),
			nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	if (nsx_start_session(&session) == -1)
		return (nsx_free_session(&session),
			nsx_putstr_fd("Error\n", 2), EXIT_FAILURE);
	nsx_free_session(&session);
	return (0);
}
