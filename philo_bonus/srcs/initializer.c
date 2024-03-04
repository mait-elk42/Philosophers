/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:14:30 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/04 16:53:43 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	nsx_init_data(t_session *session, int ac, char **av)
{
	session->data.num_philos = nsx_atoi(av[1]);
	session->data.time_die = nsx_atoi(av[2]);
	session->data.time_eat = nsx_atoi(av[3]);
	session->data.time_sleep = nsx_atoi(av[4]);
	session->data.num_meals = -1;
	if (ac == 6)
		session->data.num_meals = nsx_atoi(av[5]);
}
