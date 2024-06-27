/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:41:54 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/27 17:37:59 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_dead);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->lock_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->lock_dead);
	return (0);
}

static void	*process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		if (ft_usleep(1))
		{
			ft_putendl_fd("Error: usleep failed", 2);
			return (NULL);
		}
	}
	while (!check_dead_loop(philo))
	{
		if (start_eating(philo))
			return (NULL);
		if (start_sleeping(philo))
			return (NULL);
		if (start_thinking(philo))
			return (NULL);
	}
	return (arg);
}

static pthread_t	create_thread(t_manager *manager, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	controller;

	if (pthread_create(&controller, NULL, &control, manager->philos))
	{
		terminate("Error: Creating thread failed", manager, forks);
		return (0);
	}
	i = 0;
	while (i < manager->philos->n_philos)
	{
		if (pthread_create(&manager->philos[i].thread, NULL,
				&process, &manager->philos[i]))
		{
			terminate("Error: Creating thread failed", manager, forks);
			break ;
		}
		i++;
	}
	return (controller);
}

void	execute(t_manager *manager, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	controller;

	controller = create_thread(manager, forks);
	if (!controller)
		return ;
	// i = 0;
	// if (pthread_create(&controller, NULL, &control, manager->philos))
	// {
	// 	terminate("Error: Creating thread failed", manager, forks);
	// 	return ;
	// }
	// while (i < manager->philos->n_philos)
	// {
	// 	if (pthread_create(&manager->philos[i].thread, NULL,
	// 			&process, &manager->philos[i]))
	// 	{
	// 		terminate("Error: Creating thread failed", manager, forks);
	// 		return ;
	// 	}
	// 	i++;
	// }
	if (pthread_join(controller, NULL))
	{
		terminate("Error: Joining thread failed", manager, forks);
		return ;
	}
	i = 0;
	while (i < manager->philos->n_philos)
	{
		if (pthread_join(manager->philos[i].thread, NULL))
		{
			terminate("Error: Joining thread failed", manager, forks);
			return ;
		}
		i++;
	}
}
