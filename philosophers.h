/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:10:40 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/10 12:12:37 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>

// # define BLUE "\033[0;34m"
// # define GREEN "\033[0;32m"
// # define YELLOW "\033[0;33m"
// # define NEUTRAL "\033[0m"
// # define PURPLE "\033[0;35m"

# define BLUE ""
# define GREEN ""
# define YELLOW ""
# define NEUTRAL ""
# define PURPLE ""

int		ft_printf(char *str, ...);

typedef struct s_philo
{
	int				l_fork;
	int				r_fork;
	unsigned int	time_eat;
	int				eat_counter;
	int				id;
	struct	s_env	*env;
	pthread_t		t_id;
}	t_philo;

typedef struct s_env
{
	int				nb_philo;
	int				starting;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_dead;
	int				all_ate;
	int				nb_eat;
	unsigned int	start_time;
	pthread_mutex_t	eating;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
	t_philo 		*philos;
}	t_env;

#endif