/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:47:26 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/21 15:19:23 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_only_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			printf("Error\nArgument contains non digit char !\n");
			return (0);
		}
	}
	return (1);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf("Error\nWrong number of arguments !\n");
		return (0);
	}
	i = 0;
	while (++i < ac)
	{
		if (ft_atoll(av[i]) > MAX_INT)
		{
			printf("Error\nArgument contains overflow number !\n");
			return (0);
		}
		if (!ft_only_digit(av[i]))
			return (0);
		if (ft_strlen(av[i]) > 10 || ft_atoll(av[i]) <= 0)
		{
			printf("Error\nArgument contains negative number !\n");
			return (0);
		}	
	}
	return (1);
}
