/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:39:38 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/12 17:32:43 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	philo_timestamp(t_list *philos, char *action, useconds_t t)
{
	useconds_t	time;
	t_philo		*philo;

	philo = philos->content;
	if (!philo->data->died)
	{
		time = philo_get_time() - philo->data->init_time;
		printf("[\033[1;39m%06u\033[0;39m] \033[1;96m%d \033[0;39m%s\n", time, philo->id, action);
		ft_usleep(t);
	}
}

void	*get_forks(void *node)
{
	t_list		*philos;
	t_philo		*philo;
	t_philo		*next;
	int			i;

	i = -1;
	philos = (struct s_list *)node;
	philo = philos->content;
	next = philos->next->content;
	if (!(philo->id % 2))
		ft_usleep(10);
	while (philo->data->repeat_count == -2 || ++i < philo->data->repeat_count)
	{
		pthread_mutex_lock(&philo->fork_lock);
		philo_timestamp(philos, PHILO_TAKE_FORK, 0);
		pthread_mutex_lock(&next->fork_lock);
		philo_timestamp(philos, PHILO_TAKE_FORK, 0);
		pthread_mutex_lock(&philo->last_meal_lock);
		philo->last_meal = philo_get_time() - philo->data->init_time;
		philo_timestamp(philos, PHILO_EAT, philo->data->eat_time);
		pthread_mutex_unlock(&philo->last_meal_lock);
		philo_timestamp(philos, PHILO_SLEEP, 0);
		pthread_mutex_unlock(&next->fork_lock);
		pthread_mutex_unlock(&philo->fork_lock);
		ft_usleep(philo->data->sleep_time);
		philo_timestamp(philos, PHILO_THINK, 0);
	}
	return (NULL);
}

void	*philo_init(int philo_count, t_list *philos)
{
	int				i;
	t_list			*start;
	t_philo			*philo;

	i = -1;
	start = philos;
	while (++i < philo_count)
	{
		philo = start->content;
		if (pthread_create(&philo->thread_id, NULL, get_forks, start))
			return (philo_exit(philos, NULL, THREAD_FAILED));
		start = start->next;
	}
	while (1)
	{
		philo = start->content;
		if (philo_get_time() - philo->data->init_time - \
			philo->last_meal >= philo->data->die_time)
		{
			philo_timestamp(start, PHILO_DIE, 0);
			philo->data->died = 1;
			return (NULL);
		}
		start = start->next;
	}
	return (NULL);
}
