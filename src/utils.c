/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:17:18 by asohrabi          #+#    #+#             */
/*   Updated: 2024/07/02 11:24:04 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int	ft_atoi(char *str)
{
	int					sign;
	int					i;
	unsigned long long	a;

	a = 0;
	i = 0;
	sign = 1;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == '\v')
		|| (str[i] == '\f') || (str[i] == '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - '0');
		i++;
	}
	return (sign * a);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (1);
		i++;
	}
	return (0);
}

time_t	current_time(void)
{
	struct timeval	now;
	time_t			time_ms;

	if (gettimeofday(&now, NULL) == -1)
	{
		ft_putendl_fd("Error: Gettimeofday failed", 2);
		return (-1);
	}
	time_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time_ms);
}

int	ft_usleep(time_t ms)
{
	time_t	start;

	start = current_time();
	if (start == -1)
		return (1);
	if (ms > 5 && usleep(1000 * (ms - 5)) == -1)
		return (1);
	while ((current_time() - start) < ms)
		if (usleep(500) == -1)
			return (1);
	return (0);
}
