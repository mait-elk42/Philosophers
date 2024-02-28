/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:42:32 by mait-elk          #+#    #+#             */
/*   Updated: 2024/02/28 19:24:20 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	_nsx_put_philo_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->printf_mutex);
	printf("%zu %d %s\n", _nsx_get_time() - philo->session_data->start_time, philo->id, msg);
	pthread_mutex_unlock(philo->printf_mutex);
}

void	_nsx_philo_think(t_philo *philo)
{
	_nsx_put_philo_status(philo, "is thinking");
}

void	_nsx_philo_take_forks_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	_nsx_put_philo_status(philo, "has taken a fork");
	_nsx_put_philo_status(philo, "is thinking");
	pthread_mutex_lock(philo->right_fork);
	_nsx_put_philo_status(philo, "has taken a fork");
	_nsx_put_philo_status(philo, "is eating");
	pthread_mutex_lock(&philo->time_mutex);
	philo->last_meal_time = _nsx_get_time();
	_nsx_sleep(philo->session_data->time_to_eat);
	if (philo->n_of_meals != -1)
		philo->n_of_meals--;
	pthread_mutex_unlock(&philo->time_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
void	_nsx_philo_sleep(t_philo *philo)
{
	_nsx_put_philo_status(philo, "is sleeping");
	_nsx_sleep(philo->session_data->time_to_sleep);
}