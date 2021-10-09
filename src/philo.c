/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:39:38 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 21:05:03 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

void	philo_timestamp(t_philo *philo, t_philo_action action, useconds_t dur)
{
	useconds_t	time;

	time = philo_get_time() - philo->data.init_time;
	ft_putchar_fd('[', 1);
	ft_putnchar_fd('0', 1, 6 - ft_nbrlen(time, 10));
	ft_putnbr_fd(time, 1);
	ft_putchar_fd(']', 1);
	ft_putstr_fd(" philosopher #", 1);
	ft_putnbr_fd(philo->id, 1);
	if (action == philo_eat)
		ft_putstr_fd(" is eating 🍝\n", 1);
	if (action == philo_sleep)
		ft_putstr_fd(" is sleeping 🌙\n", 1);
	if (action == philo_think)
		ft_putstr_fd(" is thinking 🤔\n", 1);
	if (action == philo_take_fork)
		ft_putstr_fd(" has taken a fork 🔱\n", 1);
	if (action == philo_die)
		ft_putstr_fd(" died 💀\n", 1);
	ft_usleep(dur);
}

void	*test(void *arr)
{
	t_philo	*philo;

	philo = (struct s_philo *)arr;
	philo_timestamp(philo, philo_die, philo->data.die_time);
	return (NULL);
}

void	*philo_init(int philo_count, t_philo **arr)
{
	int			i;
	useconds_t	init_time;

	i = -1;
	init_time = philo_get_time();
	while (++i < philo_count)
	{
		arr[i]->data.init_time = init_time;
		if (pthread_create(&arr[i]->thread_id, NULL, test, arr[i]))
			return (philo_exit(arr, NULL, THREAD_FAILED));
		pthread_join(arr[i]->thread_id, NULL);
	}
	return (NULL);
}
