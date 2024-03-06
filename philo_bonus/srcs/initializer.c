/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:14:30 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/06 11:21:51 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	nsx_init_data(t_data *data, int ac, char **av)
{
	data->num_philos = nsx_atoi(av[1]);
	data->time_die = nsx_atoi(av[2]);
	data->time_eat = nsx_atoi(av[3]);
	data->time_sleep = nsx_atoi(av[4]);
	data->num_meals = -1;
	if (ac == 6)
		data->num_meals = nsx_atoi(av[5]);
	data->start_time = nsx_get_time();
	sem_unlink("printf_lock");
	sem_unlink("forks_lock");
	data->printf_lock = sem_open("printf_lock", O_CREAT | O_RDWR, 0666, 1);
	data->forks_lock =  sem_open("forks_lock",
		O_CREAT | O_RDWR, 0666, data->num_philos);
}

int	nsx_init_session(t_session *session)
{
	int	i;
	char	*itoa_tmp;

	session->philos = malloc(sizeof(t_philo) * session->data.num_philos);
	if (session->philos == NULL)
		return (-1);
	i = 0;
	while (i < session->data.num_philos)
	{
		session->philos[i].id = i+1;
		session->philos[i].last_meal_time = session->data.start_time;
		session->philos[i].n_of_meals = 0;
		session->philos[i].data = session->data;
		itoa_tmp = nsx_itoa(i+1);
		if (itoa_tmp == NULL)
			return (-1);
		sem_unlink(itoa_tmp);
		session->philos[i].lock = sem_open(itoa_tmp, O_CREAT | O_RDWR, 0666, 1);
		free(itoa_tmp);
		i++;
	}
	return (0);
}
