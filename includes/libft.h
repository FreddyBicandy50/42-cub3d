/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:14:20 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/05 19:36:33 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_atoi(const char *str);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *str);
char	**ft_split(char *s, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t num, size_t size);
int		ft_isdigit(unsigned char get_chars);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
#endif