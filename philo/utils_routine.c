/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:13:21 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/21 19:13:50 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_compare(t_philo *philo)
{
	return (!(philo->id == 1 && philo->env->args->nb_philo % 2 != 1));
}

void	ft_drop_fork(t_philo *philo, int num_fork)
{
	if (num_fork == 1)
	{
		if (ft_compare(philo))
			pthread_mutex_unlock(&(philo->env->forks[philo->r_fork]));
		else
			pthread_mutex_unlock(&(philo->env->forks[philo->l_fork]));
	}
	else if (num_fork == 2)
	{
		if (ft_compare(philo))
			pthread_mutex_unlock(&(philo->env->forks[philo->l_fork]));
		else
			pthread_mutex_unlock(&(philo->env->forks[philo->r_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->env->forks[philo->l_fork]));
		pthread_mutex_unlock(&(philo->env->forks[philo->r_fork]));
	}
}

void	ft_arti_delay(t_philo *philo, char *msg)
{
	pthread_mutex_unlock(&(philo->env->death));
	pthread_mutex_lock(&(philo->env->death));
	if (!philo->env->monitor->dead)
	{
		pthread_mutex_unlock(&(philo->env->death));
		pthread_mutex_lock(&(philo->env->death));
		if (!philo->env->monitor->dead)
			ft_print_logs(philo, msg);
		pthread_mutex_unlock(&(philo->env->death));
	}
	else
		pthread_mutex_unlock(&(philo->env->death));
}

void	ft_finish_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->env->last));
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&(philo->env->last));
	ft_opti_sleep(philo->env->args->time_eat);
	ft_drop_fork(philo, 3);
	pthread_mutex_lock(&(philo->env->eating));
	philo->nb_eat++;
	pthread_mutex_unlock(&(philo->env->eating));
}
