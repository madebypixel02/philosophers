/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:04:47 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 12:31:50 by aperez-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TOOLS_H

# define LIBFT_TOOLS_H

# include <unistd.h>
# include <stdlib.h>

/* Returns length of string */
size_t		ft_strlen(const char *s);

/* Prints string with write */
int			ft_putstr_fd(char *s, int fd);

/* Returns 1 if a char is of a space form: space, tab, etc */
int			ft_isspace(char c);

/* Returns 1 if c is a number in the ASCII table */
int			ft_isdigit(int c);

/* Returns equivalent int from a string, or -1 */
long long	ft_atoi(const char *nptr);

/* Writes char to given fd */
int			ft_putchar_fd(char c, int fd);

/* Writes unsigned long number to given fd */
int			ft_putnbr_fd(int n, long unsigned fd);

#endif
