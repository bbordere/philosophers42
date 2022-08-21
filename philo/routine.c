/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 10:57:15 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/20 10:57:15 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take_forks(t_philo *philo)
{
	if (ft_take_fork1(philo))
		return (1);
	if (philo->l_fork == philo->r_fork)
	{
		pthread_mutex_unlock(&(philo->env->forks[philo->l_fork]));
		return (1);
	}
	if (ft_take_fork2(philo))
		return (1);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->env->death));
	if (philo->env->monitor->dead)
	{
		pthread_mutex_unlock(&(philo->env->death));
		ft_drop_fork(philo, 3);
		return (1);
	}
	pthread_mutex_unlock(&(philo->env->death));
	pthread_mutex_lock(&(philo->env->death));
	if (!philo->env->monitor->dead)
	{
		// ft_arti_delay(philo, "is eating");
		ft_print_logs(philo, "is eating");
		pthread_mutex_unlock(&(philo->env->death));		
	}
	else
	{
		ft_drop_fork(philo, 3);
		pthread_mutex_unlock(&(philo->env->death));
		return (1);
	}
	ft_finish_eat(philo);
	return (0);
}

int	ft_sleep_think(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->env->death));
	if (philo->env->dead)
		return (pthread_mutex_unlock(&(philo->env->death)), 1);
	pthread_mutex_unlock(&(philo->env->death));
	pthread_mutex_lock(&(philo->env->death));
	if (!philo->env->dead)
		ft_arti_delay(philo, msg);
	else
		pthread_mutex_unlock(&(philo->env->death));
	if (!ft_strcmp(msg, "is sleeping"))
		ft_opti_sleep(philo->env->args->time_sleep);
	return (0);
}

int		ft_routine(t_philo *philo, int *eat_counter)
{
	// if (philo->id % 2)
	// 	usleep(1000);
	if (ft_take_forks(philo))
		return (1);
	usleep(10);
	if (ft_eat(philo))
		return (1);
	usleep(10);
	if (ft_sleep_think(philo, "is sleeping"))
		return (1);
	usleep(10);
	if (ft_sleep_think(philo, "is thinking"))
		return (1);
	(*eat_counter)++;	
	return (0);
}


void	*ft_life(void *philo_v)
{
	t_philo	*philo;
	int		eat_counter;

	philo = (t_philo *)philo_v;
	eat_counter = 0;
	if (philo->id % 2 == philo->env->args->nb_philo % 2)
		usleep(15000);
	pthread_mutex_lock(&(philo->env->last));
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&(philo->env->last));
	while ((eat_counter < philo->env->args->nb_eat
			|| philo->env->args->nb_eat == -1))
	{
		if (ft_routine(philo, &eat_counter))
			return (NULL);
	}
	return (NULL);
}
