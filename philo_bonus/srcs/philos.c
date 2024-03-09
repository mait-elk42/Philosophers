/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:16:36 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/08 19:22:50 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	nsx_put_philo_status(t_philo *philo, char *status)
{
	sem_wait(philo->data.printf_lock);
	printf("%zu %d %s\n", nsx_get_time()
		- philo->data.start_time, philo->id, status);
	sem_post(philo->data.printf_lock);
}
