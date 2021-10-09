/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:03:14 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 16:54:24 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "libft_tools.h"
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

/* Enum to handle errors in philosophers */
typedef enum e_philo_err
{
	END = 1,
	INV_ARGS = -1,
	INV_PHILO_COUNT = -2,
	INV_DIE_TIME = -3,
	INV_EAT_TIME = -4,
	INV_SLEEP_TIME = -5,
	INV_REPEAT_COUNT = -6,
	NO_MEMORY = -7,
	THREAD_FAILED = -8
}			t_philo_err;

/* Struct to handle info for every philosopher */
typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	int			fork;
	int			dead;
}				t_philo;

/* Struct to store all data */
typedef struct s_philo_data
{
	int			philo_count;
	long long	die_time;
	long long	eat_time;
	long long	sleep_time;
	long		repeat_count;
	t_philo		**arr;
}				t_philo_data;

/* Prints error message with custom param given an error code */
int			philo_perror(char *param, t_philo_err err_code);

/* Prints error message and exits freeing everything */
void		*philo_exit(t_philo_data *d, char *param, t_philo_err err_code);

/* Personal & more precise implementation of the usleep function */
int			ft_usleep(useconds_t usec);

/* Returns current time in miliseconds */
useconds_t	philo_get_time(struct timeval *t);

/* Fills an array with the default info for every philosopher */
t_philo		**philo_arr(int philo_count);

/* Creates threads for every philosopher */
void		*philo_init(t_philo_data *d);

#endif
