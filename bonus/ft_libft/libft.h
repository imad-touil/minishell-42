/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sael-kha <sael-kha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:52:50 by sael-kha          #+#    #+#             */
/*   Updated: 2024/10/21 21:52:50 by sael-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdint.h>

int		ft_toupper(int ch);
int		ft_tolower(int ch);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char const *s);
char	*ft_strchr(const char *s1, int s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memcpy(void *to, const void *from, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_itoa(int n);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int ch);
void	*ft_calloc(size_t num, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putendl_fd(char *s, int fd);

#endif
