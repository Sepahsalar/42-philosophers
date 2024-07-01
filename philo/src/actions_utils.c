/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:38:05 by asohrabi          #+#    #+#             */
/*   Updated: 2024/07/01 14:14:15 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_log(t_philo *philo, char *str, int dead)
{
	time_t	time;

	if (pthread_mutex_lock(philo->lock_write))
		return (ft_error("Error: Mutex lock failed"));
	time = current_time();
	if (time == -1)
		return (1);
	time = time - philo->start_time;
	if (!check_lock_dead(philo))
	{
		if (dead == 0)
			printf("%ld\t%d\t%s\n", time, philo->id, str);
		else
			printf(ANSI_COLOR_RED"%ld\t%d\t%s\n"ANSI_COLOR_RESET,
				time, philo->id, str);
	}
	if (pthread_mutex_unlock(philo->lock_write))
		return (ft_error("Error: Mutex unlock failed"));
	return (0);
}

int	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}
