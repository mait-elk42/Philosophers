/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:30:10 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/08 17:00:08 by mait-elk         ###   ########.fr       */
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
		pthread_mutex_destroy(&session->philos[i].meal_mutex);
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

void	nsx_sleep_ms(size_t ms, t_philo	*philo)
{
	size_t	start_time;

	(void)philo;
	start_time = nsx_get_time();
	while ((nsx_get_time() - start_time) < ms)
	{
		pthread_mutex_lock(philo->printf_mutex);
		if (*philo->someone_died)
			return (pthread_mutex_unlock(philo->printf_mutex), (void)0);
		pthread_mutex_unlock(philo->printf_mutex);
		usleep(50);
	}
}

int	nsx_atoi(char *num)
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
