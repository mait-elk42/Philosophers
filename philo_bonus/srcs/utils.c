/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:48:24 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/04 11:27:54 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

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

int		nsx_put_error()
{
	printf("Error\n");
	return (-1);
}