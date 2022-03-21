/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:32:17 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/19 10:32:17 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_args
{
	int				nb_philo;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	int				nb_eat;
}	t_args;

typedef struct s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;	
	unsigned long	last_eat;
	int				nb_eat;
	struct s_env	*env;
	pthread_t		t_id;
}	t_philo;

typedef struct s_env
{
	t_args				*args;
	t_philo				*philos;
	struct s_monitor	*monitor;
	unsigned long		start;
	int					dead;
	pthread_mutex_t		printing;
	pthread_mutex_t		eating;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death;
}	t_env;

typedef struct s_monitor
{
	int			dead;
	int			eat_counter;
	t_args		*args;
	t_philo		*philos;
	pthread_t	t_id;
}	t_monitor;

t_args			*ft_init_args(int ac, char **av);
void			ft_init_philo(t_env *env);
t_monitor		*ft_init_monitor(t_args *args, t_philo *philos);
t_env			*ft_init_env(t_args *args);
void			ft_init_mutex(t_env *env);
void			*ft_free_struct(t_env *env);
void			ft_eating(t_env	*env, t_philo *philo);
void			*ft_life(void *philo_v);
void			*ft_monitor(void *env_v);
void			ft_opti_sleep(unsigned long duration);
unsigned long	ft_get_time(void);
int				ft_isdigit(int c);
void			*ft_free_struct(t_env *env);
void			ft_exit(t_env *env);
long long		ft_atoll(char *str);
void			ft_print_logs(t_philo *philo, char *msg);
int				ft_check_args(int ac, char **av);

#endif
