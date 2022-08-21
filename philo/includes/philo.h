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
	pthread_mutex_t		strt;
	pthread_mutex_t		last;
	pthread_mutex_t		eating;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death;
	pthread_mutex_t		nb_eat;
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
t_monitor		*ft_init_monitor(t_args *args, t_philo *philos);
t_env			*ft_init_env(t_args *args);

int				ft_strlen(char *str);
int				ft_only_digit(char *str);
int				ft_check_args(int ac, char **av);
int				ft_isdigit(int c);
int				ft_strcmp(char *s1, char *s2);
int				ft_check_all_ate(t_env *env, t_philo *philos);
int				ft_take1(t_philo *philo);
int				ft_take2(t_philo *philo);
int				ft_take_fork1(t_philo *philo);
int				ft_take_fork2(t_philo *philo);
int				ft_compare(t_philo *philo);
int				ft_monitoring(t_env *env);
int				ft_take_forks(t_philo *philo);
int				ft_eat(t_philo *philo);
int				ft_sleep_think(t_philo *philo, char *msg);
int				ft_routine(t_philo *philo, int *eat_counter);

long long		ft_atoll(char *str);

unsigned long	ft_get_time(void);

void			*ft_monitor(void *env_v);
void			ft_check_death(t_env *env, int i);
void			*ft_life(void *philo_v);
void			ft_init_mutex(t_env *env);
void			ft_init_philo(t_env *env);
void			ft_opti_sleep(unsigned long duration);
void			ft_lock_proper_fork(t_philo *philo, int num_fork);
void			ft_print_logs(t_philo *philo, char *msg);
void			ft_exit(t_env *env);
void			*ft_free_struct(t_env *env);
void			ft_drop_fork(t_philo *philo, int num_fork);
void			ft_arti_delay(t_philo *philo, char *msg);
void			ft_finish_eat(t_philo *philo);
void			*ft_monitor(void *env_v);
void			ft_create_threads(t_env *env);

#endif
