/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:28:13 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/04 17:24:08 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int main(int ac, char **av)
{
	t_session	session;
	int			i;

	i = 0;
	if (nsx_valid_args(ac, av) != -1)
	{
		nsx_init_data(&session, ac, av);
		session.philo = malloc(sizeof(t_philo) * session.data.num_philos);
		while (i < session.data.num_philos)
		{
			session.philo[i].pid = fork();
			if (session.philo[i].pid == 0)
			{
				printf("child n %d\n", getpid());
				return (0);
			}
			i++;
		}
	}
	else
		return (nsx_put_error());
	return (EXIT_SUCCESS);
}
