/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 11:03:54 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/20 11:03:54 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

long long	ft_atoll(char *str)
{
	int			i;
	long long	res;
	long long	s;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '-' && str[i])
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+' && str[i])
		i++;
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (s * res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_print_logs(t_philo *philo, char *msg)
{
	if (philo->env->monitor->dead && !ft_strcmp(msg, "is eating"))
	{
		pthread_mutex_unlock(&(philo->env->forks[philo->l_fork]));
		pthread_mutex_unlock(&(philo->env->forks[philo->r_fork]));
		return ;
	}
	if (philo->env->monitor->dead && ft_strcmp(msg, "died"))
		return ;
	pthread_mutex_lock(&(philo->env->printing));
	printf("%lu %d %s\n", ft_get_time() - philo->env->start,
		philo->id + 1, msg);
	pthread_mutex_unlock(&(philo->env->printing));
}
