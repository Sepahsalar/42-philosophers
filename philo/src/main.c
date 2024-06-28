/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:13:32 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/28 14:45:04 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_args(char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[1]) > MAX_PHILO)
	{
		ft_putendl_fd("Error: Too many philosophers entered.", 2);
		return (1);
	}
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			ft_putendl_fd("Error: Arguments should be positive numbers.", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_manager		manager;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	if (argc != 5 && argc != 6)
	{
		ft_putendl_fd("Error: Invalid number of arguments", 2);
		return (1);
	}
	if (check_args(argv))
		return (1);
	init_manager(&manager, philos);
	init_forks(&manager, forks, ft_atoi(argv[1]));
	init_philos(&manager, philos, forks, argv);
	execute(&manager, forks);
	terminate(NULL, &manager, forks);
	return (0);
}
