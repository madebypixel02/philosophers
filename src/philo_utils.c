/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:58:29 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 12:22:01 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

useconds_t	philo_get_time(struct timeval *t)
{
	gettimeofday(t, NULL);
	return (t->tv_sec * 1000 + t->tv_usec / 1000);
}

int	ft_usleep(useconds_t usec)
{
	struct timeval	t;
	useconds_t		before;
	useconds_t		after;

	before = philo_get_time(&t);
	after = before;
	while (after - before < usec)
	{
		if (usleep(usec / 10 + 1) == -1)
			return (-1);
		after = philo_get_time(&t);
	}
	return (0);
}

int	philo_perror(char *param, t_philo_err err_code)
{
	ft_putstr_fd("philo: ", 2);
	if (err_code == INV_ARGS)
		ft_putstr_fd("invalid number of arguments", 2);
	if (err_code == INV_PHILO_COUNT)
		ft_putstr_fd("invalid philosopher_count: ", 2);
	if (err_code == INV_DIE_TIME)
		ft_putstr_fd("invalid time_to_die: ", 2);
	if (err_code == INV_EAT_TIME)
		ft_putstr_fd("invalid time_to_eat: ", 2);
	if (err_code == INV_SLEEP_TIME)
		ft_putstr_fd("invalid time_to_sleep: ", 2);
	if (err_code == INV_REPEAT_COUNT)
		ft_putstr_fd("invalid repeat_times: ", 2);
	if (param && err_code != INV_ARGS)
		ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	*philo_exit(char *param, t_philo_err err_code)
{
	if (err_code != END)
		philo_perror(param, err_code);
	return (0);
}
