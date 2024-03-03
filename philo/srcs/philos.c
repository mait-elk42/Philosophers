/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:42:32 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/03 10:35:46 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	nsx_put_philo_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->printf_mutex);
	printf("%zu %d %s\n", nsx_get_time()
		- philo->cp_data.start_time, philo->id, msg);
	pthread_mutex_unlock(philo->printf_mutex);
}

void	nsx_philo_think(t_philo *philo)
{
	nsx_put_philo_status(philo, PHILO_THINK);
}

void	nsx_philo_take_forks_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	nsx_put_philo_status(philo, PHILO_TAKEN_A_FORK);
	nsx_put_philo_status(philo, PHILO_THINK);
	pthread_mutex_lock(philo->right_fork);
	nsx_put_philo_status(philo, PHILO_TAKEN_A_FORK);
	nsx_put_philo_status(philo, PHILO_EAT);
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	philo->last_meal_time = nsx_get_time();
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	pthread_mutex_lock(&philo->n_meals_mutex);
	if (philo->n_of_meals != -1)
		philo->n_of_meals--;
	pthread_mutex_unlock(&philo->n_meals_mutex);
	nsx_sleep(philo->cp_data.time_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	nsx_philo_sleep(t_philo *philo)
{
	nsx_put_philo_status(philo, PHILO_SLEEP);
	nsx_sleep(philo->cp_data.time_sleep);
}
