/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:30:10 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/03 22:01:54 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	nsx_putstr_fd(char	*str, int fd)
{
	if (str)
		while (*str)
			write(fd, str++, 1);
}

void	nsx_free_session(t_session *session)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&session->printf_mutex);
	while (session->forks && i < session->data.num_philos)
		pthread_mutex_destroy(&session->forks[i++]);
	i = 0;
	while (session->philos && i < session->data.num_philos)
	{
		pthread_mutex_destroy(&session->philos[i].n_meals_mutex);
		pthread_mutex_destroy(&session->philos[i].last_meal_time_mutex);
		i++;
	}
	free(session->forks);
	free(session->philos);
}

size_t	nsx_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	nsx_sleep_ms(size_t ms)
{
	size_t	start_time;

	start_time = nsx_get_time();
	while ((nsx_get_time() - start_time) < ms)
		usleep(100);
}
