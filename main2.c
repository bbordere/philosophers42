/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:04:52 by bbordere          #+#    #+#             */
/*   Updated: 2022/03/17 16:26:18 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p.h"

void	ft_init_philo(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
	{
		env->philos[i].id = i;
		env->philos[i].l_fork = i;
		env->philos[i].r_fork = (env->philos[i].id + 1) % env->nb_philo;
		env->philos[i].eat_counter = 0;
		env->philos[i].env = env;
	}
}

void	*ft_free_philo(t_env *env, t_philo *philos)
{
	free(philos);
	free(env);
	return (NULL);
}

void	ft_init_mutex(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
		pthread_mutex_init(&(env->forks[i]), NULL);
	pthread_mutex_init(&(env->printing), NULL);
	pthread_mutex_init(&(env->eating), NULL);
	pthread_mutex_init(&(env->death), NULL);	
}

t_env *ft_init_env(int ac, char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->nb_philo = atoi(av[1]);
	env->time_die = atoi(av[2]);
	env->time_eat = atoi(av[3]);
	env->time_sleep = atoi(av[4]);
	env->nb_dead = 0;
	env->all_ate = 0;
	env->starting = 0;
	if (ac == 6)
		env->nb_eat = atoi(av[5]);
	else
		env->nb_eat = -1;
	env->philos = malloc(sizeof(t_philo) * (env->nb_philo));
	if (!env->philos)
		return (ft_free_philo(env, NULL));
	env->forks = malloc(sizeof(pthread_mutex_t) * (env->nb_philo));
	if (!env->forks)
		return (ft_free_philo(env, env->philos));
	ft_init_philo(env);
	ft_init_mutex(env);
	return (env);
}

unsigned int ft_get_time(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void		ft_opti_sleep(t_env *env, unsigned int duration)
{
	unsigned int	t;

	t = ft_get_time();
	while (!env->nb_dead && ft_get_time() - t < duration)
		usleep(20);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 0;
	while (++i < ac)
		if (atoi(av[i]) <= 0)
			return (-1);
	return (0);
}

void	ft_print_logs(t_env *env, int philo_id, char *msg)
{
	if (env->nb_dead || env->all_ate)
		return ;
	pthread_mutex_lock(&(env->printing));
	printf("%s%u%s %d %s\n", YELLOW, ft_get_time() - env->start_time, NEUTRAL, philo_id + 1, msg);
	pthread_mutex_unlock(&(env->printing));
}

int	ft_take_right_fork(t_env *env, t_philo *philo)
{
	pthread_mutex_lock(&(env->forks[philo->r_fork]));
	ft_print_logs(env, philo->id, BLUE"has taken a fork");
	pthread_mutex_lock(&(env->forks[philo->l_fork]));
	ft_print_logs(env, philo->id, BLUE"has taken a fork");
	return (1);
}

int	ft_take_left_fork(t_env *env, t_philo *philo)
{
	pthread_mutex_lock(&(env->forks[philo->l_fork]));
	ft_print_logs(env, philo->id, BLUE"has taken a fork");
	pthread_mutex_lock(&(env->forks[philo->r_fork]));
	ft_print_logs(env, philo->id, BLUE"has taken a fork");
	return (2);
}

void	ft_eating(t_env	*env, t_philo *philo)
{
	int	fork;

	if (env->nb_dead)
		return ;
	if (philo->r_fork < philo->l_fork)
		fork = ft_take_right_fork(env, philo);
	else
		fork = ft_take_left_fork(env, philo);
	pthread_mutex_lock(&(env->eating));
	philo->last_eat = ft_get_time();
	ft_print_logs(env, philo->id, PURPLE"is eating");
	pthread_mutex_unlock(&(env->eating));
	philo->eat_counter++;
	ft_opti_sleep(env, env->time_eat);
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

void	*ft_actions(void *philo_v)
{
	t_philo	*philo;
	t_env	*env;
	int		c;

	philo = (t_philo *)philo_v;
	env = philo->env;
	c = 0;
	if (philo->id % 2)
		ft_opti_sleep(env, env->time_eat);
	while (!env->nb_dead)
	{
		if (env->nb_eat == -1 || c < env->nb_eat)
		{
			ft_eating(env, philo);
			ft_print_logs(env, philo->id, GREEN"is sleeping");
			ft_opti_sleep(env, env->time_sleep);
			ft_print_logs(env, philo->id, GREEN"is thinking");
			c++;
		}
		pthread_mutex_lock(&env->death);
		env->nb_dead = philo->dead;
		pthread_mutex_unlock(&env->death);
	}
	return (NULL);	
}

void	*ft_death(t_env *env, t_philo *philo)
{
		pthread_mutex_lock(&(env->death));
		philo->dead = 1;
		ft_print_logs(env, philo->id, "die");
		pthread_mutex_unlock(&(env->death));
		return (NULL);
}

void	*ft_papa(void *env_v)
{
	t_env	*env;
	t_philo	*philos;
	int 	i;
	unsigned int	t;

	env = (t_env *)env_v;
	philos = env->philos;
	i = -1;
	while (++i < env->nb_philo)
	{
		t = ft_get_time() - philos[i].last_eat;
		if (t > (unsigned int)env->time_die)
		{
			ft_death(env, &philos[i]);
			return ;
		}
	}
	return (NULL);
}

void	ft_exit(t_env *env, pthread_t papa)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
		pthread_join(env->philos[i].t_id, NULL);
	pthread_join(papa, NULL);
	i = -1;
	while (++i < env->nb_philo)
		pthread_mutex_destroy(&(env->forks[i]));
	pthread_mutex_destroy(&(env->printing));
	pthread_mutex_destroy(&(env->eating));
	free(env->forks);
	ft_free_philo(env, env->philos);	
}

void	ft_create_threads(t_env *env)
{
	int	i;
	unsigned int	t;
	t_philo			*philos;
	pthread_t		papa;

	i = -1;
	t = ft_get_time();
	env->start_time = t;
	philos = env->philos;
	papa = 0;
	while (++i < env->nb_philo)
	{
		philos[i].last_eat = t;
		pthread_create(&(philos[i].t_id), NULL, ft_actions, &philos[i]);
	}
	pthread_create(&papa, NULL, ft_papa, env);
	ft_exit(env, papa);
}

int main(int ac, char **av)
{
	t_env	*env;

	if (ft_check_args(ac, av) == -1)
		return (1);
	env = ft_init_env(ac, av);
	if (!env)
		return (1);
	ft_create_threads(env);
	return (0);
}