/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:03:01 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 14:58:13 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

static t_philo_data	parse_args(char **argv)
{
	t_philo_data	d;

	d.philo_count = ft_atoi(argv[1]);
	if (d.philo_count <= 0)
		philo_exit(NULL, argv[1], INV_PHILO_COUNT);
	d.die_time = ft_atoi(argv[2]);
	if (d.die_time == -1)
		philo_exit(NULL, argv[2], INV_DIE_TIME);
	d.eat_time = ft_atoi(argv[3]);
	if (d.eat_time == -1)
		philo_exit(NULL, argv[3], INV_EAT_TIME);
	d.sleep_time = ft_atoi(argv[4]);
	if (d.sleep_time == -1)
		philo_exit(NULL, argv[4], INV_SLEEP_TIME);
	d.repeat_count = -2;
	if (argv[5])
	{
		d.repeat_count = ft_atoi(argv[5]);
		if (d.repeat_count == -1)
			philo_exit(NULL, argv[5], INV_REPEAT_COUNT);
	}
	return (d);
}

int	main(int argc, char **argv)
{
	t_philo_data	d;
	int				i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		philo_exit(NULL, NULL, INV_ARGS);
		return (1);
	}
	d = parse_args(argv);
	if (d.philo_count <= 0 || d.die_time == -1 || d.eat_time == -1 \
		|| d.sleep_time == -1 || d.repeat_count == -1)
		return (1);
	d.arr = philo_arr(d.philo_count);
	while (d.arr && d.arr[i])
	{
		printf("Philosopher #%d\n", d.arr[i]->id);
		i++;
	}
	philo_exit(&d, NULL, END);
	return (0);
}
