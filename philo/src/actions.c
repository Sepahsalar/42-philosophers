/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:23:58 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/28 11:34:04 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_log(t_philo *philo, char *str, int dead)
{
	time_t	time;

	pthread_mutex_lock(philo->lock_write);
	time = current_time() - philo->start_time;
	if (!check_dead_loop(philo))
	{
		if (dead == 0)
			printf("%ld %d %s\n", time, philo->id, str);
		else
			printf(ANSI_COLOR_RED"%ld %d %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(philo->lock_write);
}

static int	ft_usleep_error(void)
{
	ft_putendl_fd("Error: usleep failed", 2);
	return (1);
}

int	start_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, "has taken a fork", 0);
	if (philo->n_philos == 1)
	{
		if (ft_usleep(philo->t_die))
			return (ft_usleep_error());
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, "has taken a fork", 0);
	philo->is_eating = 1;
	print_log(philo, "is eating", 0);
	pthread_mutex_lock(philo->lock_meal);
	philo->last_meal = current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->lock_meal);
	if (ft_usleep(philo->t_eat))
		return (ft_usleep_error());
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	start_sleeping(t_philo *philo)
{
	print_log(philo, "is sleeping", 0);
	if (ft_usleep(philo->t_sleep))
	{
		ft_putendl_fd("Error: usleep failed", 2);
		return (1);
	}
	return (0);
}

int	start_thinking(t_philo *philo)
{
	print_log(philo, "is thinking", 0);
	return (0);
}
