/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 11:01:10 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/20 11:01:10 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_opti_sleep(unsigned long duration)
{
	unsigned long	t;
	if (duration <= 0)
		return ;
	t = ft_get_time();
	while (ft_get_time() - t < duration)
		usleep(50);
}
