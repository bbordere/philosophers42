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

void	ft_create_threads(t_env *env)
{
	int				i;
	unsigned long	start;
	t_philo			*philos;

	i = -1;
	start = ft_get_time();
	env->start = start;
	philos = env->philos;
	while (++i < env->args->nb_philo)
	{
		philos[i].last_eat = start;
		pthread_create(&(philos[i].t_id), NULL, &ft_life, &philos[i]);
	}
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
