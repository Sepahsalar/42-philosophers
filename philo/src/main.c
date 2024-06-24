/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:13:32 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/24 16:52:07 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_args(char **argv)
{
	int	i;

	i = 1;
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
	if (argc != 5 && argc != 6)
	{
		ft_putendl_fd("Error: Invalid number of arguments", 2);
		return (1);
	}
	if (check_args(argv))
		return (1);
	return (0);
}
