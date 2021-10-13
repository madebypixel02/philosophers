/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:03:14 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/13 13:41:57 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include "libft_tools.h"
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

# define PHILO_EAT "\033[1;93mis eating 🍝\033[0;39m"
# define PHILO_SLEEP "\033[1;95mis sleeping 🌙\033[0;39m"
# define PHILO_THINK "\033[1;90mis thinking 💭\033[0;39m"
# define PHILO_TAKE_FORK "\033[1;94mhas taken a fork 🍴\033[0;39m"
# define PHILO_DIE "\033[1;91mdied 💀\033[0;39m"

/* Enum to handle errors in philosophers */
typedef enum e_philo_err
{
	END = 1,
	INV_ARGS = -1,
	TOO_MANY_PHILO = -2,
	INV_PHILO_COUNT = -3,
	INV_DIE_TIME = -4,
	INV_EAT_TIME = -5,
	INV_SLEEP_TIME = -6,
	INV_REPEAT_COUNT = -7,
	NO_MEMORY = -8,
	THREAD_FAILED = -9
}			t_philo_err;

/* Struct to store all data */
typedef struct s_philo_data
{
	int				philo_count;
	useconds_t		init_time;
	long			repeat_count;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long			eat_count;
	pthread_mutex_t	eat_count_lock;
	int				died;
	pthread_mutex_t	died_lock;
}					t_philo_data;

/* Struct to handle info for every philosopher */
typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	pthread_mutex_t		fork_lock;
	useconds_t			last_meal;
	pthread_mutex_t		last_meal_lock;
	struct s_philo_data	*data;
}						t_philo;

/* Prints error message with custom param given an error code */
int			philo_perror(char *param, t_philo_err err_code);

/* Prints error message and exits freeing everything */
void		*philo_exit(t_list *philos, char *param, t_philo_err err_code);

/* Personal & more precise implementation of the usleep function */
int			ft_usleep(useconds_t usec);

/* Returns current time in miliseconds */
useconds_t	philo_get_time(void);

/* Fills an array with the default info for every philosopher */
t_list		*philo_lst(t_philo_data *d);

/* Creates threads for every philosopher */
void		*philo_init(int philo_count, t_list *philos);

/* Prints current state of a philosopher if applicable */
void		philo_timestamp(t_list *philos, char *action, useconds_t t);

#endif
