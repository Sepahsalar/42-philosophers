/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:52 by asohrabi          #+#    #+#             */
/*   Updated: 2024/07/01 14:22:06 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	count_eating_philos(t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philos->n_philos)
	{
		if (pthread_mutex_lock(philos->lock_meal))
		{
			ft_putendl_fd("Error: Mutex lock failed", 2);
			return (-1);
		}
		if (philos[i].meals_eaten >= philos->n_eat)
			count++;
		if (pthread_mutex_unlock(philos->lock_meal))
		{
			ft_putendl_fd("Error: Mutex unlock failed", 2);
			return (-1);
		}
		i++;
	}
	return (count);
}

int	check_finished_eating(t_philo *philos)
{
	int	count;

	count = 0;
	if (philos->n_eat == -1)
		return (0);
	count = count_eating_philos(philos);
	if (count == -1)
		return (1);
	if (count == philos->n_philos)
	{
		if (pthread_mutex_lock(philos->lock_dead))
			return (ft_error("Error: Mutex lock failed"));
		*(philos->dead) = 1;
		if (pthread_mutex_unlock(philos->lock_dead))
			return (ft_error("Error: Mutex unlock failed"));
		return (1);
	}
	return (0);
}

static int	check_starved(t_philo *philo)
{
	time_t	time;

	if (pthread_mutex_lock(philo->lock_dead))
		return (ft_error("Error: Mutex lock failed"));
	time = current_time();
	if (time == -1)
		return (1);
	if (time - philo->last_meal >= philo->t_die
		&& philo->is_eating == 0)
	{
		if (pthread_mutex_unlock(philo->lock_dead))
			return (ft_error("Error: Mutex unlock failed"));
		return (1);
	}
	if (pthread_mutex_unlock(philo->lock_dead))
		return (ft_error("Error: Mutex unlock failed"));
	return (0);
}

static int	check_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->n_philos)
	{
		if (check_starved(&philos[i]))
		{
			if (print_log(&philos[i], "died", 1))
				return (1);
			if (pthread_mutex_lock(philos->lock_dead))
				return (ft_error("Error: Mutex lock failed"));
			*(philos->dead) = 1;
			if (pthread_mutex_unlock(philos->lock_dead))
				return (ft_error("Error: Mutex unlock failed"));
			return (1);
		}
		i++;
	}
	return (0);
}

void	*control(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (check_dead(philos) || check_finished_eating(philos))
			break ;
	}
	return (arg);
}
