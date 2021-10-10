/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:39:38 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/10 20:04:39 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_timestamp(t_list *philos, char *action)
{
	useconds_t	time;
	t_philo		*philo;

	philo = philos->content;
	time = philo_get_time() - philo->data->init_time;
	printf("[%06u] philosopher #%d %s\n", time, philo->id, action);
}

void	*get_forks(void *node)
{
	t_list		*philos;
	t_philo		*philo;
	t_philo		*next;

	philos = (struct s_list *)node;
	philo = philos->content;
	next = philos->next->content;
	if (!(philo->id % 2))
		ft_usleep(10);
	pthread_mutex_lock(&philo->fork_lock);
	philo_timestamp(philos, PHILO_TAKE_FORK);
	pthread_mutex_lock(&next->fork_lock);
	philo_timestamp(philos, PHILO_TAKE_FORK);
	ft_usleep(500);
	philo_timestamp(philos, PHILO_EAT);
	ft_usleep(500);
	pthread_mutex_unlock(&next->fork_lock);
	pthread_mutex_unlock(&philo->fork_lock);
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
	i = -1;
	while (++i < philo_count)
		pthread_join(philo->thread_id, NULL);
	return (NULL);
}
