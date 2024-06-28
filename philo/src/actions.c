/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:23:58 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/28 15:54:59 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_log(t_philo *philo, char *str, int dead)
{
	time_t	time;

	if (pthread_mutex_lock(philo->lock_write))
	{
		ft_putendl_fd("Error: Mutex lock failed", 2);
		return (1);
	}
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
	{
		ft_putendl_fd("Error: Mutex lock failed", 2);
		return (1);
	}
	return (0);
}

static int	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int	start_eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork))
		return (ft_error("Error: Mutex lock failed"));
	if (print_log(philo, "has taken a fork", 0))
		return (1);
	if (philo->n_philos == 1)
	{
		if (ft_usleep(philo->t_die))
			return (ft_error("Error: Usleep failed"));
		if (pthread_mutex_unlock(philo->r_fork))
			return (ft_error("Error: Mutex unlock failed"));
		return (0);
	}
	if (pthread_mutex_lock(philo->l_fork))
		return (ft_error("Error: Mutex lock failed"));
	if (print_log(philo, "has taken a fork", 0))
		return (1);
	philo->is_eating = 1;
	if (print_log(philo, "is eating", 0))
		return (1);
	if (pthread_mutex_lock(philo->lock_meal))
		return (ft_error("Error: Mutex lock failed"));
	philo->last_meal = current_time();
	if (philo->last_meal == -1)
		return (1);
	philo->meals_eaten++;
	if (pthread_mutex_unlock(philo->lock_meal))
		return (ft_error("Error: Mutex unlock failed"));
	if (ft_usleep(philo->t_eat))
		return (ft_error("Error: Usleep failed"));
	philo->is_eating = 0;
	if (pthread_mutex_unlock(philo->l_fork))
		return (ft_error("Error: Mutex unlock failed"));
	if (pthread_mutex_unlock(philo->r_fork))
		return (ft_error("Error: Mutex unlock failed"));
	return (0);
}

int	start_sleeping(t_philo *philo)
{
	if (print_log(philo, "is sleeping", 0))
		return (1);
	if (ft_usleep(philo->t_sleep))
	{
		ft_putendl_fd("Error: Usleep failed", 2);
		return (1);
	}
	return (0);
}

int	start_thinking(t_philo *philo)
{
	if (print_log(philo, "is thinking", 0))
		return (1);
	return (0);
}
