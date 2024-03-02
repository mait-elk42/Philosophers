/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:42:32 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/02 22:58:23 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	nsx_put_philo_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->printf_mutex);
	printf("%zu %d %s\n", nsx_get_time()
		- philo->cp_data.start_time, philo->id, msg);
	pthread_mutex_unlock(philo->printf_mutex);
}

void	nsx_philo_think(t_philo *philo)
{
	nsx_put_philo_status(philo, "is thinking");
}

void	nsx_philo_take_forks_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	nsx_put_philo_status(philo, "has taken a fork");
	nsx_put_philo_status(philo, "is thinking");
	pthread_mutex_lock(philo->right_fork);
	nsx_put_philo_status(philo, "has taken a fork");
	nsx_put_philo_status(philo, "is eating");
	pthread_mutex_lock(&philo->meals_mutex);
	philo->last_meal_time = nsx_get_time();
	if (philo->n_of_meals != -1)
		philo->n_of_meals--;
	pthread_mutex_unlock(&philo->meals_mutex);
	nsx_sleep(philo->cp_data.time_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	nsx_philo_sleep(t_philo *philo)
{
	nsx_put_philo_status(philo, "is sleeping");
	nsx_sleep(philo->cp_data.time_sleep);
}
