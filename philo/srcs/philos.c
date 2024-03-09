/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:42:32 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/09 14:00:00 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	nsx_put_philo_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->printf_mutex);
	if (*philo->someone_died)
		return (pthread_mutex_unlock(philo->printf_mutex), 1);
	printf("%zu %d %s\n", nsx_get_time()
		- philo->cp_data.start_time, philo->id, msg);
	pthread_mutex_unlock(philo->printf_mutex);
	return (0);
}

int	nsx_philo_take_forks_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	nsx_put_philo_status(philo, PHILO_TAKEN_A_FORK);
	nsx_put_philo_status(philo, PHILO_THINK);
	pthread_mutex_lock(philo->right_fork);
	nsx_put_philo_status(philo, PHILO_TAKEN_A_FORK);
	nsx_put_philo_status(philo, PHILO_EAT);
	nsx_sleep_ms(philo->cp_data.time_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = nsx_get_time();
	if (philo->n_of_meals != -1)
		philo->n_of_meals--;
	if (philo->n_of_meals == 0)
		return (pthread_mutex_unlock(&philo->meal_mutex), 1);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}
