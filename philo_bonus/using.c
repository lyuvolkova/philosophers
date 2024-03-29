/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:45:48 by lubov             #+#    #+#             */
/*   Updated: 2022/02/07 23:46:06 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isnumb(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_isspace(int c)
{
	if (c == 32 || c == 9 || c == 10 || c == 11 || \
		c == 12 || c == 13)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		num;
	int		minus;

	i = 0;
	num = 0;
	minus = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (int)str[i] - 48;
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (num * minus);
}

long	get_time(void)
{
	struct timeval	*time;
	long			res;

	time = malloc(sizeof(struct timeval));
	gettimeofday(time, NULL);
	res = 1000 * time->tv_sec + time->tv_usec / 1000;
	return (res);
}
