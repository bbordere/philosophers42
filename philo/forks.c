/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 19:12:03 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/21 19:12:43 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lock_proper_fork(t_philo *philo, int num_fork)
{
	if (num_fork == 1)
	{
		if (ft_compare(philo))
			pthread_mutex_lock(&(philo->env->forks[philo->r_fork]));
		else
			pthread_mutex_lock(&(philo->env->forks[philo->l_fork]));
	}
	else
	{
		if (ft_compare(philo))
			pthread_mutex_lock(&(philo->env->forks[philo->l_fork]));
		else
			pthread_mutex_lock(&(philo->env->forks[philo->r_fork]));		
	}
}

int		ft_take1(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->env->death));
	ft_lock_proper_fork(philo, 1);
	pthread_mutex_lock(&(philo->env->death));
	if (!philo->env->monitor->dead)
		ft_print_logs(philo, "has taken a fork");
	else
	{
		pthread_mutex_unlock(&(philo->env->death));
		ft_drop_fork(philo, 1);
		return (1);
	}
	pthread_mutex_unlock(&(philo->env->death));
	return (0);
}

int		ft_take2(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->env->death));
	ft_lock_proper_fork(philo, 2);
	pthread_mutex_lock(&(philo->env->death));
	if (!philo->env->monitor->dead)
		ft_print_logs(philo, "has taken a fork");
	else
	{
		pthread_mutex_unlock(&(philo->env->death));
		ft_drop_fork(philo, 3);
		return (1);
	}
	pthread_mutex_unlock(&(philo->env->death));
	return (0);
}

int	ft_take_fork1(t_philo *philo)
{
	pthread_mutex_lock(&(philo->env->death));
	if (philo->env->monitor->dead)
		return (pthread_mutex_unlock(&(philo->env->death)), 1);
	pthread_mutex_unlock(&(philo->env->death));
	pthread_mutex_lock(&(philo->env->death));
	if (!philo->env->monitor->dead)
	{
		if (ft_take1(philo))
			return (1);
	}
	else
		return (pthread_mutex_unlock(&(philo->env->death)), 1);
	return (0);
}

int	ft_take_fork2(t_philo *philo)
{
	pthread_mutex_lock(&(philo->env->death));
	if (philo->env->monitor->dead)
	{
		pthread_mutex_unlock(&(philo->env->death));
		ft_drop_fork(philo, 1);
		return (1);
	}
	pthread_mutex_unlock(&(philo->env->death));
	pthread_mutex_lock(&(philo->env->death));
	if (!philo->env->monitor->dead)
	{
		if (ft_take2(philo))
			return (1);
	}
	else
	{
		ft_drop_fork(philo, 1);
		pthread_mutex_unlock(&(philo->env->death));
		return (1);
	}
	return (0);
}