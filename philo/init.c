/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:53:52 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/20 10:53:52 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	*ft_init_args(int ac, char **av)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->nb_philo = ft_atoll(av[1]);
	args->time_die = (unsigned long)ft_atoll(av[2]);
	args->time_eat = (unsigned long)ft_atoll(av[3]);
	args->time_sleep = (unsigned long)ft_atoll(av[4]);
	if (ac == 6)
		args->nb_eat = ft_atoll(av[5]);
	else
		args->nb_eat = -1;
	return (args);
}

void	ft_init_philo(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->args->nb_philo)
	{
		env->philos[i].id = i;
		env->philos[i].l_fork = i;
		env->philos[i].r_fork = (env->philos[i].id + 1) % env->args->nb_philo;
		env->philos[i].nb_eat = 0;
		env->philos[i].env = env;
		env->philos[i].last_eat = 0;
	}	
}

t_monitor	*ft_init_monitor(t_args *args, t_philo *philos)
{
	t_monitor	*monitor;

	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	monitor->dead = 0;
	monitor->eat_counter = 0;
	monitor->args = args;
	monitor->philos = philos;
	return (monitor);
}

t_env	*ft_init_env(t_args *args)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->args = args;
	env->dead = 0;
	env->philos = malloc(sizeof(t_philo) * (env->args->nb_philo));
	if (!env->philos)
		return (ft_free_struct(env));
	env->forks = malloc(sizeof(pthread_mutex_t) * (env->args->nb_philo));
	if (!env->forks)
		return (ft_free_struct(env));
	env->monitor = ft_init_monitor(args, env->philos);
	ft_init_philo(env);
	ft_init_mutex(env);
	return (env);
}

void	ft_init_mutex(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->args->nb_philo)
		pthread_mutex_init(&(env->forks[i]), NULL);
	pthread_mutex_init(&(env->printing), NULL);
	pthread_mutex_init(&(env->eating), NULL);
	pthread_mutex_init(&(env->death), NULL);
	pthread_mutex_init(&(env->strt), NULL);
	pthread_mutex_init(&(env->last), NULL);
}
