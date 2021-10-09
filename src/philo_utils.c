/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:58:29 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 20:29:17 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	**philo_arr(t_philo_data d)
{
	int		i;
	t_philo	**arr;

	i = -1;
	arr = malloc(sizeof (t_philo *) * (d.philo_count + 1));
	if (!arr)
		return (philo_exit(NULL, NULL, NO_MEMORY));
	while (++i < d.philo_count)
	{
		arr[i] = malloc(sizeof(struct s_philo));
		if (!arr[i])
		{
			free(arr);
			return (philo_exit(NULL, NULL, NO_MEMORY));
		}
		arr[i]->id = i + 1;
		arr[i]->thread_id = 0;
		pthread_mutex_init(&arr[i]->mutex, NULL);
		arr[i]->fork_available = 1;
		arr[i]->is_dead = 0;
		arr[i]->data = d;
	}
	arr[i] = NULL;
	return (arr);
}

useconds_t	philo_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_usleep(useconds_t usec)
{
	useconds_t		before;
	useconds_t		after;

	before = philo_get_time();
	after = before;
	while (after - before < usec)
	{
		if (usleep(usec / 10 + 1) == -1)
			return (-1);
		after = philo_get_time();
	}
	return (0);
}

int	philo_perror(char *param, t_philo_err err_code)
{
	ft_putstr_fd("philo: ", 2);
	if (err_code == INV_ARGS)
		ft_putstr_fd("invalid number of arguments", 2);
	if (err_code == NO_MEMORY)
		ft_putstr_fd("no memory left on device", 2);
	if (err_code == THREAD_FAILED)
		ft_putstr_fd("failed to create a thread", 2);
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
	if (param && err_code != INV_ARGS && err_code != NO_MEMORY && \
			err_code != THREAD_FAILED)
		ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	*philo_exit(t_philo **arr, char *param, t_philo_err err_code)
{
	if (err_code != END)
		philo_perror(param, err_code);
	if (arr)
		ft_free_matrix((char ***)&arr);
	return (NULL);
}
