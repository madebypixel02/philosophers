/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-b <aperez-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:04:47 by aperez-b          #+#    #+#             */
/*   Updated: 2021/10/09 20:49:12 by aperez-b         ###   ########.fr       */
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
int			ft_putnbr_fd(long unsigned n, int fd);

/* Frees a char ** accordingly */
void		ft_free_matrix(char ***m);

/* Writes n chars sequentially */
int			ft_putnchar_fd(char c, int fd, int n);

/* Returns length of a number in a given base */
int			ft_nbrlen(long n, int base);

#endif
