/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:30:10 by mait-elk          #+#    #+#             */
/*   Updated: 2024/02/27 16:40:20 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	_nsx_putstr_fd(char	*str, int fd)
{
	if (str)
		while (*str)
			write(fd, str++, 1);
}

void	_nsx_free_session(t_session *session)
{
	free(session->forks);
	free(session->philos);
}

size_t	_nsx_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	_nsx_sleep(size_t ms)
{
	size_t	start_time;

	start_time = _nsx_get_time();
	while ((_nsx_get_time() - start_time) < ms);
}
