/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:03:14 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 10:33:57 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "libft_tools.h"
# include <stdio.h>

/* Enum to handle errors in philosophers */
typedef enum e_philo_err
{
	END = 1,
	INV_ARGS = -1,
	INV_PHILO_COUNT = -2,
	INV_DIE_TIME = -3,
	INV_EAT_TIME = -4,
	INV_SLEEP_TIME = -5,
	INV_REPEAT_COUNT = -6
}			t_philo_err;

/* Struct to store all data */
typedef struct s_philo_data
{
	int					philo_count;
	long long unsigned	die_time;
	long long unsigned	eat_time;
	long long unsigned	sleep_time;
	long				repeat_count;
}				t_philo_data;

/* Prints error message with custom param given an error code */
int		philo_perror(char *param, t_philo_err err_code);

/* Prints error message and exits freeing everything */
void	*philo_exit(char *param, t_philo_err err_code);

#endif
