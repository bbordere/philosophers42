/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 11:02:55 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/20 11:02:55 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_env *env)
{
	int	i;

	i = -1;
	pthread_join(env->monitor->t_id, NULL);
	while (++i < env->args->nb_philo)
		pthread_join(env->philos[i].t_id, NULL);
	i = -1;
	while (++i < env->args->nb_philo)
		pthread_mutex_destroy(&(env->forks[i]));
	pthread_mutex_destroy(&(env->printing));
	pthread_mutex_destroy(&(env->eating));
	ft_free_struct(env);
}

void	*ft_free_struct(t_env *env)
{
	if (env->args)
		free(env->args);
	if (env->forks)
		free(env->forks);
	if (env->monitor)
		free(env->monitor);
	if (env->philos)
		free(env->philos);
	free(env);
	return (NULL);
}
