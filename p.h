/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:02:35 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/17 14:12:14 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>

# define BLUE ""
# define GREEN ""
# define YELLOW ""
# define NEUTRAL ""
# define PURPLE ""

typedef struct s_philo
{
	int				l_fork;
	int				r_fork;
	int				id;
	unsigned int	last_eat;
	int				eat_counter;
	int				dead;
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
	int				all_ate;
	int				nb_dead;
	int				nb_eat;
	unsigned int	start_time;
	pthread_mutex_t	death;
	pthread_mutex_t	eating;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printing;
	t_philo 		*philos;
}	t_env;