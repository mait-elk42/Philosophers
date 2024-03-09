/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:28:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/09 00:59:47 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	nsx_free_all_exit(t_session *session)
{
	int	i;

	i  = 0;
	while (i < session->philos->data.num_philos)
	{
		sem_close(session->philos->data.forks_lock);
		sem_close(session->philos->data.printf_lock);
		sem_close(session->philos->lock);
		i++;
	}
	free(session->philos);
	exit(EXIT_SUCCESS);
}

void	*death_thread(void *p)
{
	t_philo	*philo;
	size_t	last_meal_time;

	philo = (t_philo *)p;
	while (1)
	{
		sem_wait(philo->lock);
		last_meal_time = nsx_get_time() - philo->last_meal_time;
		if (philo->n_of_meals
			&& last_meal_time >= (size_t)philo->data.time_die)
		{
			sem_wait(philo->data.printf_lock);
			printf("%zu %d is died\n", last_meal_time, philo->id);
			exit(13);
		}
		sem_post(philo->lock);
	}
}

int	philo_life(t_philo *philo)
{
	pthread_t	death_check;

	pthread_create(&death_check, NULL, &death_thread, philo);
	pthread_detach(death_check);
	while (1)
	{
		sem_wait(philo->data.forks_lock);
		nsx_put_philo_status(philo, "has taken a fork");
		sem_wait(philo->data.forks_lock);
		nsx_put_philo_status(philo, "has taken a fork");
		nsx_put_philo_status(philo, "is eating");
		nsx_sleep_ms(philo->data.time_eat);
		sem_post(philo->data.forks_lock);
		sem_post(philo->data.forks_lock);
		sem_wait(philo->lock);
		philo->last_meal_time = nsx_get_time();
		if (philo->n_of_meals != -1)
			philo->n_of_meals--;
		if (philo->n_of_meals == 0)
			exit(0);
		sem_post(philo->lock);
		nsx_put_philo_status(philo, "is sleep");
		nsx_sleep_ms(philo->data.time_sleep);
		nsx_put_philo_status(philo, "is thinking");
	}
}

void	kill_all_chproc(t_session	*session, int ret)
{
	int	i;

	i = 0;
	if (ret == 13)
	{
		while (i < session->philos->data.num_philos)
			kill(session->philos[i++].pid, SIGINT);
		nsx_free_all_exit(session);
	}
}

int	main(int ac, char **av)
{
	t_session	session;
	int			ret;
	int			i;

	i = 0;
	if (nsx_valid_args(ac, av) != -1)
	{
		nsx_init_data(&session.data, ac, av);
		if (nsx_init_session(&session) == -1)
			return (free(session.philos), EXIT_FAILURE);
		while (i < session.data.num_philos)
		{
			session.philos[i].pid = fork();
			if (session.philos[i].pid == 0)
				return (philo_life(&session.philos[i]));
			i++;
		}
	}
	else
		return (printf("Error\n"), EXIT_FAILURE);
	while (waitpid(-1, &ret, 0) != -1)
		kill_all_chproc(&session, WEXITSTATUS(ret));
	nsx_free_all_exit(&session);
	return (EXIT_SUCCESS);
}
