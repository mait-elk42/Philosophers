/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:30:10 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/07 22:38:44 by mait-elk         ###   ########.fr       */
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

void	nsx_sleep_ms(size_t ms)
{
	size_t	start_time;

	start_time = nsx_get_time();
	while ((nsx_get_time() - start_time) < ms);
		// usleep(100);
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