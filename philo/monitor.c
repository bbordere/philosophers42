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
		if (philos[i].nb_eat < env->args->nb_eat)
			return (0);
	return (1);
}

void	*ft_death(t_env *env, int i)
{
	pthread_mutex_lock(&(env->death));
	env->monitor->dead = 1;
	pthread_mutex_unlock(&(env->death));
	ft_print_logs(&env->philos[i], "died");
	pthread_mutex_unlock(&(env->eating));
	return (NULL);
}

void	*ft_monitor(void *env_v)
{
	t_env			*env;
	unsigned long	t;
	int				i;

	env = (t_env *)env_v;
	i = -1;
	while (++i < env->args->nb_philo)
	{
		t = ft_get_time();
		pthread_mutex_lock(&(env->eating));
		if (ft_check_all_ate(env, env->philos))
		{	
			pthread_mutex_unlock(&(env->eating));
			return (NULL);
		}
		if ((t - env->philos[i].last_eat) > env->args->time_die)
			return (ft_death(env, i));
		pthread_mutex_unlock(&(env->eating));
		if (i == env->args->nb_philo - 1)
			i = -1;
	}
	return (NULL);
}
