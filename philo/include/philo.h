/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:13:40 by asohrabi          #+#    #+#             */
/*   Updated: 2024/07/01 13:57:46 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define MAX_PHILO 300
# define ANSI_COLOR_RED "\001\x1b[31m\002"
# define ANSI_COLOR_RESET "\001\x1b[0m\002"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	int				meals_eaten;
	time_t			start_time;
	time_t			last_meal;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*lock_write;
	pthread_mutex_t	*lock_dead;
	pthread_mutex_t	*lock_meal;
}					t_philo;

typedef struct s_manager
{
	int				is_dead;
	t_philo			*philos;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_meal;
}					t_manager;

void	ft_putendl_fd(char *s, int fd);
int		ft_atoi(char *str);
int		ft_isdigit(char *str);
time_t	current_time(void);
int		ft_usleep(time_t ms);
void	terminate(char *str, t_manager *manager, pthread_mutex_t *forks);
void	init_manager(t_manager *manager, t_philo *philos);
void	init_forks(t_manager *manager, pthread_mutex_t *forks, int num_forks);
void	init_philos(t_manager *manager, t_philo *philos, pthread_mutex_t *forks,
			char **argv);
int		check_lock_dead(t_philo *philo);
int		start_eating(t_philo *philo);
int		start_sleeping(t_philo *philo);
int		start_thinking(t_philo *philo);
int		print_log(t_philo *philo, char *str, int dead);
void	execute(t_manager *manager, pthread_mutex_t *forks);
void	*control(void *arg);
int		check_finished_eating(t_philo *philos);
int		ft_error(char *str);

#endif
