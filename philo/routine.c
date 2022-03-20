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

int	ft_take_right_fork(t_env *env, t_philo *philo)
{
	pthread_mutex_lock(&(env->forks[philo->r_fork]));
	ft_print_logs(philo, "has taken a fork");
	pthread_mutex_lock(&(env->forks[philo->l_fork]));
	ft_print_logs(philo, "has taken a fork");
	return (1);
}

int	ft_take_left_fork(t_env *env, t_philo *philo)
{
	pthread_mutex_lock(&(env->forks[philo->l_fork]));
	ft_print_logs(philo, "has taken a fork");
	pthread_mutex_lock(&(env->forks[philo->r_fork]));
	ft_print_logs(philo, "has taken a fork");
	return (2);
}

void	ft_eating(t_env	*env, t_philo *philo)
{
	int	fork;

	if (philo->r_fork < philo->l_fork)
		fork = ft_take_right_fork(env, philo);
	else
		fork = ft_take_left_fork(env, philo);
	pthread_mutex_lock(&(env->eating));
	philo->last_eat = ft_get_time();
	ft_print_logs(philo, "is eating");
	philo->nb_eat++;
	pthread_mutex_unlock(&(env->eating));
	ft_opti_sleep(env->args->time_eat);
	if (fork == 1)
	{
		pthread_mutex_unlock(&(env->forks[philo->l_fork]));
		pthread_mutex_unlock(&(env->forks[philo->r_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(env->forks[philo->r_fork]));
		pthread_mutex_unlock(&(env->forks[philo->l_fork]));
	}
}

void	*ft_life(void *philo_v)
{
	t_philo	*philo;
	int		dead;
	int		eat_counter;

	philo = (t_philo *)philo_v;
	dead = 0;
	eat_counter = 0;
	if (philo->id % 2)
		ft_opti_sleep(philo->env->args->time_eat);
	while (!dead && (eat_counter < philo->env->args->nb_eat
			|| philo->env->args->nb_eat == -1))
	{
		ft_eating(philo->env, philo);
		ft_print_logs(philo, "is sleeping");
		ft_opti_sleep(philo->env->args->time_sleep);
		ft_print_logs(philo, "is thinking");
		pthread_mutex_lock(&(philo->env->death));
		dead = philo->env->monitor->dead;
		eat_counter++;
		pthread_mutex_unlock(&(philo->env->death));
	}
	return (NULL);
}
