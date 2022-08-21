/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:59:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/20 10:59:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_all_ate(t_env *env, t_philo *philos)
{
	int	i;

	i = -1;
	if (env->args->nb_eat == -1)
		return (0);
	while (++i < env->args->nb_philo)
	{
		pthread_mutex_lock(&(env->eating));
		if (philos[i].nb_eat < env->args->nb_eat)
			return (pthread_mutex_unlock(&(env->eating)), 0);
		pthread_mutex_unlock(&(env->eating));
	}
	return (1);
}

void	ft_check_death(t_env *env, int i)
{
	unsigned long	last;

	pthread_mutex_lock(&(env->last));
	last = env->philos[i].last_eat;
	pthread_mutex_unlock(&(env->last));
	if ((ft_get_time() - last) > env->args->time_die)
	{
		pthread_mutex_lock(&(env->death));
		env->monitor->dead = 1;
		pthread_mutex_unlock(&(env->death));
	}
}

int	ft_monitoring(t_env *env)
{
	int	i;

	pthread_mutex_lock(&(env->death));
	if (env->monitor->dead)
		return (pthread_mutex_unlock(&(env->death)), 1);
	pthread_mutex_unlock(&(env->death));
	i = -1;
	while (++i < env->args->nb_philo)
	{
		ft_check_death(env, i);
		pthread_mutex_lock(&(env->death));
		if (env->monitor->dead)
		{
			pthread_mutex_unlock(&(env->death));
			ft_print_logs(&env->philos[i], "died");
			return (1);
		}
		pthread_mutex_unlock(&(env->death));
	}
	return (0);
}

void	*ft_monitor(void *env_v)
{
	t_env	*env;

	env = (t_env *)env_v;
	while (1)
		if (ft_monitoring(env) || ft_check_all_ate(env, env->philos))
			return (NULL);
	return (NULL);
}