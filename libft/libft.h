/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:06:53 by acohaut           #+#    #+#             */
/*   Updated: 2026/02/17 15:41:42 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

/***********************LIST**********************/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstsize(t_list *lst);

/***********************LIBFT**********************/

long long	ft_atoll(const char *str);

int			ft_atoi(const char *str);
int			ft_isspace(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dest, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
size_t		ft_strnlen(const char *s, size_t size);

char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strdup(const char *s1);
char		*ft_strndup(const char *s1, size_t size);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);

void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);

/***********************GET_NEXT_LINE**********************/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# define FD_MAX 1024

char		*get_next_line(int fd);
char		*take_line(char *file);
char		*read_file(int fd, char *file);
char		*sup_line_static(char *file);
char		*ft_strjoin_gnl(char *s1, char *s2);

/***********************PRINTF**********************/

typedef struct s_flag
{
	int	plus;
	int	space;
	int	hash;
}				t_flag;

int			ft_printf_hash(va_list *args, char c);
int			ft_printf_sign(va_list *args, int is_plus, int is_space, char c);
int			is_flag(char c);
int			ft_flag_parsing(va_list *args, const char *str, int *i);
int			ft_flag_check(t_flag flags, va_list *args, char c);

void		init_struct(t_flag *flags);

char		*ft_strdup_itoa_unsigned(char *s1, int size);
char		*ft_itoa_unsigned(unsigned int n);

int			is_format(char c);
int			ft_format_printf(va_list *args, char c);
int			ft_printf(const char *str, ...);
int			ft_printf_char(int c);
int			ft_printf_str(const char *str);
int			ft_printf_nbr(int nb);
int			ft_printf_unsigned(unsigned int nb);
int			ft_printf_hexa(unsigned int nb, int uppercase);
int			ft_printf_ptr(void *address);

void		ft_hexa_ptr(unsigned long long nb);

#endif
