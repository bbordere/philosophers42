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

t_env *ft_init_env(int ac, char **av)
{
	t_env	*env;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->nb_philo = av[1];
	env->time_die = av[2];
	env->time_eat = av[3];
	env->time_sleep = av[4];
	if (ac == 6);
		env->nb_eat = av[5];
	else
		env->nb_eat = -1;
}