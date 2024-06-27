/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:13:40 by asohrabi          #+#    #+#             */
/*   Updated: 2024/06/27 12:35:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_PHILO 300

typedef struct s_philo
{
	pthread_t		thread;
	int				id; //
	int				is_eating; //
	int				meals_eaten; //
	time_t			start_time;
	time_t			last_meal;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				*dead; //
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock; //
	pthread_mutex_t	*dead_lock; //
	pthread_mutex_t	*meal_lock; //
}					t_philo;

void	ft_putendl_fd(char *s, int fd);
int		ft_atoi(char *str);
int		ft_isdigit(char *str);

#endif
