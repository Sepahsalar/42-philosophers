/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:41:54 by asohrabi          #+#    #+#             */
/*   Updated: 2024/07/02 11:27:26 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_lock_dead(t_philo *philo)
{
	if (pthread_mutex_lock(philo->lock_dead))
		return (ft_error("Error: Mutex lock failed"));
	if (*(philo->dead) == 1)
	{
		if (pthread_mutex_unlock(philo->lock_dead))
			return (ft_error("Error: Mutex unlock failed"));
		return (1);
	}
	if (pthread_mutex_unlock(philo->lock_dead))
		return (ft_error("Error: Mutex unlock failed"));
	return (0);
}

static void	*process(void *arg)
{
	int		res;
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		res = usleep(3000);
	else if (philo-> id != 1 && philo->id == philo->n_philos
		&& philo->id % 2 != 0)
		res = usleep(6000);
	if (res == -1)
	{
		ft_putendl_fd("Error: Usleep failed", 2);
		return (NULL);
	}
	while (!check_lock_dead(philo))
	{
		if (start_eating(philo) || start_sleeping(philo)
			|| start_thinking(philo))
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
		if (pthread_create(&(manager->philos[i].thread), NULL,
				&process, &(manager->philos[i])))
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
