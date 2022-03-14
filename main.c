/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:14:17 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/10 12:07:38 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_philo(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
	{
		env->philos[i].id = i;
		env->philos[i].l_fork = i;
		env->philos[i].r_fork = (env->philos[i].id + 1) % env->nb_philo;
		env->philos[i].env = env;
	}
}

void	ft_init_mutex(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
		pthread_mutex_init(&(env->forks[i]), NULL);
	pthread_mutex_init(&(env->printing), NULL);
	pthread_mutex_init(&(env->eating), NULL);	
}

t_env *ft_init_env(int ac, char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->nb_philo = atoi(av[1]);
	env->time_die = atoi(av[2]);
	env->time_eat = atoi(av[3]);
	env->time_sleep = atoi(av[4]);
	env->nb_dead = 0;
	env->state_eating = 0;
	if (ac == 6)
		env->nb_eat = atoi(av[5]);
	else
		env->nb_eat = -1;
	env->philos = malloc(sizeof(t_philo) * (env->nb_philo));
	if (!env->philos)
		return (NULL); //FREE STRUCT
	env->forks = malloc(sizeof(pthread_mutex_t) * (env->nb_philo));
	if (!env->forks)
		return (NULL); //FREE STRUCT + philos
	ft_init_mutex(env);
	ft_init_philo(env);
	return (env);
}

unsigned int ft_get_time(void)
{
	static struct timeval t;
	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void		ft_opti_sleep(t_env *env, unsigned int duration)
{
	unsigned int	t;

	t = ft_get_time();
	while (!env->nb_dead && ft_get_time() - t < duration)
		usleep(10);
}

void	ft_print_logs(t_env *env, int philo_id, char *msg)
{
	if (env->nb_dead)
		return ;
	pthread_mutex_lock(&(env->printing));
	printf("\033[0;33m%u\033[0m %d %s\n", ft_get_time() - env->start_time, philo_id + 1, msg);
	pthread_mutex_unlock(&(env->printing));
}

void	ft_eating(t_env	*env, t_philo *philo)
{
	if (env->nb_dead)
		return ;
	if (philo->r_fork < philo->l_fork)
	{
		pthread_mutex_lock(&(env->forks[philo->r_fork]));
		ft_print_logs(env, philo->id, "has taken a fork");
		pthread_mutex_lock(&(env->forks[philo->l_fork]));
		ft_print_logs(env, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(env->forks[philo->l_fork]));
		ft_print_logs(env, philo->id, "has taken a fork");
		pthread_mutex_lock(&(env->forks[philo->r_fork]));
		ft_print_logs(env, philo->id, "has taken a fork");
	}
	pthread_mutex_lock(&(env->eating));
	ft_print_logs(env, philo->id, "is eating");
	philo->time_eat = ft_get_time();
	pthread_mutex_unlock(&(env->eating));
	ft_opti_sleep(env, env->time_eat);
	pthread_mutex_unlock(&(env->forks[philo->l_fork]));
	pthread_mutex_unlock(&(env->forks[philo->r_fork]));
}

void		ft_check_death(t_env *env, t_philo *philos)
{
	int	i;

	while (1) //while(not all ate)
	{
		i = -1;
		while (!env->nb_dead && ++i < env->nb_philo)
		{
			pthread_mutex_lock(&(env->eating));
			if (ft_get_time() - philos[i].time_eat > (unsigned int)env->time_die)
			{
				ft_print_logs(env, philos[i].id, "died");
				env->nb_dead++;
			}
			pthread_mutex_unlock(&(env->eating));
			usleep(100);
		}
		if (env->nb_dead)
				return ;
	}
}

void	*ft_actions(void *philo_v)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)philo_v;
	env = philo->env;
	philo->time_eat = ft_get_time();
	if (philo->id % 2)
		ft_opti_sleep(env, env->time_eat);
	while(!env->nb_dead)
	{
		ft_eating(env, philo);
		ft_print_logs(env, philo->id, "is sleeping");
		ft_opti_sleep(env, env->time_sleep);
		ft_print_logs(env, philo->id, "is thinking");
	}
	return (NULL);
}

void	ft_create_threads(t_env *env)
{
	int	i;
	t_philo *philos;

	philos = env->philos;
	env->start_time = ft_get_time();
	i = -1;
	while (++i < env->nb_philo)
		pthread_create(&(philos[i].t_id), NULL, ft_actions, &(philos[i]));
	ft_check_death(env, philos);
	i = -1;
	while (++i < env->nb_philo)
		pthread_join(philos[i].t_id, NULL);
}

int main(int ac, char **av)
{
	t_env	*env;
	env = ft_init_env(ac, av);
	ft_create_threads(env);
	return 0;
}
