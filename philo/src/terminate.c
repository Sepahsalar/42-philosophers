/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:55:15 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/27 17:04:40 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	terminate(char *str, t_manager *manager, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		ft_putendl_fd(str, 2);
	pthread_mutex_destroy(&manager->lock_write);
	pthread_mutex_destroy(&manager->lock_dead);
	pthread_mutex_destroy(&manager->lock_meal);
	while (i < manager->philos->n_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
