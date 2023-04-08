/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:44:23 by gemaroul          #+#    #+#             */
/*   Updated: 2018/10/29 23:53:22 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H
# include "../libft.h"

/*
**	print
*/

void				ft_putendl(char const *s);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);

/*
**	find and seek
*/

int					ft_strchri_lu(char *s, int c, int i);
int					ft_strchri(char *s, int c, int i);
char				*ft_strnstr(const char *haystack,
					const char *needle, size_t len);
char				*ft_strstr(const char *haystack, const char *needle);

/*
**	compare
*/

int					ft_strcmp(const char *s1, const char *s2);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);

/*
**	str creation
*/

char				*ft_strnew(size_t size);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnjoin(char const *s1, char const *s2, size_t n);
char				*ft_strjoinfree(char *ret, char *s1, char *s2);
char				*ft_strnjoinfree(char *ret, char *s1, char *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				**ft_strsplit(char const *s, char c);

/*
**	str deletion
*/

void				ft_strdel(char **as);
void				ft_strclr(char *s);

/*
**	coping
*/

char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr(const char *s, int c);
int					ft_strchr_b(char *s, int c);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/*
**	mapping
*/

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strmap(char const *s, char (*f)(char));

/*
**	len
*/

size_t				ft_wstrlen(unsigned *s);
size_t				ft_strlen(const char *s);
unsigned int		ft_wordlen(char const *s, char c);
int					ft_wordcount(char *s, char c);

/*
**	iteration
*/

void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_striter(char *s, void (*f)(char *));

/*
**	trim
*/

char				*ft_strtrim(const char *s);
char				*ft_strmove(char *str, char blnk);
char				*ft_strreplace(char *str, char n, char o, int len);
char				*ft_strtolower(char *str);
char				*ft_strunicode(wchar_t *s);

#endif
