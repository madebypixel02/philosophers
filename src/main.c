/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:03:01 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 10:33:30 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static t_philo_data	parse_args(char **argv)
{
	t_philo_data	d;
	int				ret;

	ret = ft_atoi(argv[1], (unsigned long long *)&d.philo_count);
	if (ret == -1 || !d.philo_count)
		return (*(struct s_philo_data *)philo_exit(argv[1], INV_PHILO_COUNT));
	ret = ft_atoi(argv[2], &d.die_time);
	if (ret == -1)
		return (*(struct s_philo_data *)philo_exit(argv[2], INV_DIE_TIME));
	ret = ft_atoi(argv[3], &d.eat_time);
	if (ret == -1)
		return (*(struct s_philo_data *)philo_exit(argv[3], INV_EAT_TIME));
	ret = ft_atoi(argv[4], &d.sleep_time);
	if (ret == -1)
		return (*(struct s_philo_data *)philo_exit(argv[4], INV_SLEEP_TIME));
	d.repeat_count = -1;
	if (argv[5])
	{
		ret = ft_atoi(argv[5], (unsigned long long *)&d.repeat_count);
		if (ret == -1)
			return (*(struct s_philo_data *)philo_exit(argv[5], \
				INV_REPEAT_COUNT));
	}
	return (d);
}

int	main(int argc, char **argv)
{
	t_philo_data	d;

	if (argc != 5 && argc != 6)
		return (*(int *)philo_exit(NULL, INV_ARGS));
	d = parse_args(argv);
	if (!d.philo_count)
		return (0);
	printf("%d %llu %llu %llu %ld\n", d.philo_count, d.die_time, d.eat_time, \
		d.sleep_time, d.repeat_count);
}
