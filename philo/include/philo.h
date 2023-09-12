/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:55:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 15:52:56 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>
# include <stdio.h>
# include <libc.h>		// memset used in ft_calloc

# define EARGC				1
# define EMALLOC			2
# define ECREATE_THREAD		3
# define ETHJOIN			4
# define EMUTEX				5
# define ECREATE_PHILO		6

typedef struct s_time
{
	int			health;
	int			eat;
	int			sleep;
	long int	start;
	int			n_cycles;
}				t_time;

typedef struct s_philo
{
	int				id;
	struct s_time	*time;
	int				is_turn;		// [0] start - [1] queued
	int				*fork[2];	// maybe remove
	pthread_mutex_t	*mutex[2];
}				t_philo;

typedef struct s_monastery
{
	int				n_philo;
	struct s_philo	**philo;
	struct s_time	*time;
	pthread_t		*th;
	int				*forks;		// maybe remove - but useful for visualize
	pthread_mutex_t	*mutex;
}				t_monastery;

// -------------------------------------------------------------------- PARSING
int		parse_monastery(t_monastery *data, char **argv);

// -------------------------------------------------------------------- THREADS
int		create_threads(t_monastery *data);
int		join_threads(t_monastery *data);
void	*starters(void *arg);
void	*queued(void *arg);

// ----------------------------------------------------------------------- TIME
long int	get_ms(void);
long int	get_us(void);

// ---------------------------------------------------------------------- UTILS
int		ft_atoi(const char *str);
void	*ft_calloc(size_t len, size_t n_bits);

// ---------------------------------------------------------------- PRINT UTILS
int		error(int err_code, char *file, int line);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	print_philo(t_philo *philo);

#endif
