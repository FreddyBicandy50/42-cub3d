/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbicandy <fbicandy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:14:20 by fbicandy          #+#    #+#             */
/*   Updated: 2025/08/05 13:22:12 by fbicandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_isdigit(int c);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		ft_atoi(const char *nptr);
char	**ft_split(char *s, char c);
char	*ft_strrchr(char *s, int c);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strcpy(char *dest, char *src);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		compare_chars(const char *s1, const char *s2, size_t n);

#endif