/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:59:52 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/27 18:06:52 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_finished_eating(t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (philos->n_eat == -1)
		return (0);
	while (i < philos->n_philos)
	{
		pthread_mutex_lock(philos->lock_meal);
		if (philos[i].meals_eaten >= philos->n_eat)
			count++;
		pthread_mutex_unlock(philos->lock_meal);
		i++;
	}
	if (count == philos->n_philos)
	{
		pthread_mutex_lock(philos->lock_dead);
		*(philos->dead) = 1;
		pthread_mutex_unlock(philos->lock_dead);
		return (1);
	}
	return (0);
}

static int	check_starved(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_dead);
	if (current_time() - philo->last_meal >= philo->t_die
		&& philo->is_eating == 0)
	{
		pthread_mutex_unlock(philo->lock_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->lock_dead);
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
			print_log(&philos[i], "died");
			pthread_mutex_lock(philos->lock_dead);
			*(philos->dead) = 1;
			pthread_mutex_unlock(philos->lock_dead);
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
