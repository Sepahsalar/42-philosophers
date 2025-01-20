/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:23:58 by asohrabi          #+#    #+#             */
/*   Updated: 2024/07/02 11:23:24 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	handle_single_philo(t_philo *philo)
{
	if (philo->n_philos == 1)
	{
		if (ft_usleep(philo->t_die))
			return (ft_error("Error: Usleep failed"));
		if (pthread_mutex_unlock(philo->r_fork))
			return (ft_error("Error: Mutex unlock failed"));
	}
	return (0);
}

static int	handle_forks(t_philo *philo, char c)
{
	if (c == 'L')
	{
		if (pthread_mutex_lock(philo->l_fork))
			return (ft_error("Error: Mutex lock failed"));
		if (print_log(philo, "has taken a fork", 0))
			return (1);
	}
	else
	{
		if (pthread_mutex_lock(philo->r_fork))
			return (ft_error("Error: Mutex lock failed"));
		if (print_log(philo, "has taken a fork", 0))
			return (1);
	}
	return (0);
}

int	start_eating(t_philo *philo)
{
	if (handle_forks(philo, 'R'))
		return (1);
	if (handle_single_philo(philo))
		return (1);
	if (handle_forks(philo, 'L'))
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
