/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:00:54 by asohrabi          #+#    #+#             */
/*   Updated: 2024/07/01 13:36:30 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_manager(t_manager *manager, t_philo *philos)
{
	manager->is_dead = 0;
	manager->philos = philos;
	if (pthread_mutex_init(&(manager->lock_write), NULL)
		|| pthread_mutex_init(&(manager->lock_dead), NULL)
		|| pthread_mutex_init(&(manager->lock_meal), NULL))
	{
		terminate("Error: Mutex init failed", manager, NULL);
		return ;
	}
}

void	init_forks(t_manager *manager, pthread_mutex_t *forks, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			terminate("Error: Mutex init failed", manager, forks);
			return ;
		}
		i++;
	}
}

static void	get_argv(t_philo *philo, char **argv)
{
	philo->n_philos = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->n_eat = ft_atoi(argv[5]);
	else
		philo->n_eat = -1;
}

static void	init_philos_helper(t_manager *manager, t_philo *philo,
	pthread_mutex_t *forks, int i)
{
	philo->id = i + 1;
	philo->is_eating = 0;
	philo->meals_eaten = 0;
	philo->dead = &(manager->is_dead);
	philo->r_fork = &forks[i];
	philo->lock_write = &(manager->lock_write);
	philo->lock_dead = &(manager->lock_dead);
	philo->lock_meal = &(manager->lock_meal);
}

void	init_philos(t_manager *manager, t_philo *philos, pthread_mutex_t *forks,
	char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].start_time = current_time();
		if (philos[i].start_time == -1)
		{
			terminate(NULL, manager, forks);
			return ;
		}
		philos[i].last_meal = current_time();
		if (philos[i].last_meal == -1)
		{
			terminate(NULL, manager, forks);
			return ;
		}
		get_argv(&philos[i], argv);
		init_philos_helper(manager, &philos[i], forks, i);
		if (i == 0)
			philos[i].l_fork = &forks[ft_atoi(argv[1]) - 1];
		else
			philos[i].l_fork = &forks[i - 1];
		i++;
	}
}
