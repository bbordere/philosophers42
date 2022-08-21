/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:54:34 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/19 10:54:34 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_monitor(void *env_v);

void	ft_create_threads(t_env *env)
{
	int				i;
	unsigned long	start;
	t_philo			*philos;

	i = -1;
	start = ft_get_time();
	pthread_mutex_lock(&(env->strt));
	env->start = start;
	pthread_mutex_unlock(&(env->strt));
	philos = env->philos;
	while (++i < env->args->nb_philo)
	{
		pthread_create(&(philos[i].t_id), NULL, &ft_life, &philos[i]);
	}
	usleep(60000);
	pthread_create(&env->monitor->t_id, NULL, &ft_monitor, env);
	ft_exit(env);
}

int	main(int ac, char **av)
{
	t_args	*args;
	t_env	*env;

	if (!ft_check_args(ac, av))
		return (1);
	args = ft_init_args(ac, av);
	if (!args)
		return (1);
	env = ft_init_env(args);
	if (!env)
		return (1);
	ft_create_threads(env);
	return (0);
}
