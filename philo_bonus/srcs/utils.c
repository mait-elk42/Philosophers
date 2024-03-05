/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:48:24 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/05 22:35:59 by mait-elk         ###   ########.fr       */
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

char	*nsx_itoa(int num)
{
	char	*res;
	int		i;
	int		tmpnum;

	i = 0;
	if (num <= 0)
		return (NULL);
	tmpnum = num;
	while (tmpnum)
	{
		i++;
		tmpnum /= 10;
	}
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	res[i--] = '\0';
	while (num)
	{
		res[i--] = (num % 10) + 48;
		num /= 10;
	}
	return (res);
}

size_t	nsx_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	nsx_sleep_ms(size_t ms)
{
	size_t	start_time;

	start_time = nsx_get_time();
	while ((nsx_get_time() - start_time) < ms)
		usleep(100);
}

