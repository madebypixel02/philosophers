/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:39:38 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 19:01:25 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*test(void *arr)
{
	t_philo	*aux;

	aux = (struct s_philo *)arr;
	ft_putstr_fd("Philosopher #", 1);
	ft_putnbr_fd(aux->id, 1);
	ft_putchar_fd('\n', 1);
	return (NULL);
}

void	*philo_init(t_philo_data *d)
{
	int	i;

	i = -1;
	while (++i < d->philo_count)
	{
		if (pthread_create(&d->arr[i]->thread_id, NULL, test, d->arr[i]))
			return (philo_exit(d, NULL, THREAD_FAILED));
		pthread_join(d->arr[i]->thread_id, NULL);
	}
	return (NULL);
}
