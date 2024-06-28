/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:55:15 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/28 14:40:03 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	terminate(char *str, t_manager *manager, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		ft_putendl_fd(str, 2);
	if (manager)
	{
		if (&(manager->lock_write))
			if (pthread_mutex_destroy(&(manager->lock_write)))
				ft_putendl_fd("Error: Mutex destroy failed", 2);
		if (&(manager->lock_write))
			if (pthread_mutex_destroy(&(manager->lock_dead)))
				ft_putendl_fd("Error: Mutex destroy failed", 2);
		if (&(manager->lock_write))
			if (pthread_mutex_destroy(&(manager->lock_meal)))
				ft_putendl_fd("Error: Mutex destroy failed", 2);
		while (i < manager->philos->n_philos && &(forks[i]))
		{
			if (pthread_mutex_destroy(&forks[i]))
				ft_putendl_fd("Error: Mutex destroy failed", 2);
			i++;
		}
	}
}
