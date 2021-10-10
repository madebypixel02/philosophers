/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:58:29 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/10 21:09:42 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*philo_get_data(t_philo_data *d, int i)
{
	t_philo	*node;

	node = malloc(sizeof(struct s_philo));
	if (!node)
		return (philo_exit(NULL, NULL, THREAD_FAILED));
	node->id = i + 1;
	node->thread_id = 0;
	pthread_mutex_init(&node->fork_lock, NULL);
	node->is_dead = 0;
	node->data = d;
	return (node);
}

t_list	*philo_lst(t_philo_data *d)
{
	int		i;
	t_list	*philos;

	i = -1;
	philos = NULL;
	while (++i < d->philo_count)
		ft_lstadd_back(&philos, ft_lstnew(philo_get_data(d, i)));
	return (philos);
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

void	*philo_exit(t_list *philos, char *param, t_philo_err err_code)
{
	t_list	*temp;
	t_philo	*philo;
	int		i;

	i = -1;
	if (err_code != END)
		philo_perror(param, err_code);
	if (philos)
	{
		philo = (struct s_philo *)philos->content;
		while (philo && ++i < philo->data->philo_count)
		{
			temp = philos;
			philos = philos->next;
			philo = (struct s_philo *)philos->content;
			ft_lstdelone(temp, free);
		}
	}
	return (NULL);
}
