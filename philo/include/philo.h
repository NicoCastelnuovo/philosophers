/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:55:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/13 16:22:39 by ncasteln         ###   ########.fr       */
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
# define EGET_TIME			7

typedef struct s_time
{
	int			health;
	int			eat;
	int			sleep;
	uint64_t	start;
	int			limit;
}				t_time;

typedef struct s_philo
{
	int				id;			// set to -1 if die
	struct s_time	*time;
	uint64_t		start_eat;
	uint64_t		start_think;
	uint64_t		end_think;
	int				is_turn;	// [0] start - [1] queued
	int				n_cycles;
	int				*fork[2];	// maybe remove
	pthread_mutex_t	*mutex[2];
}				t_philo;

typedef struct s_monastery
{
	int				n_philo;
	struct s_philo	**philo;
	struct s_time	*time;
	pthread_t		*th;
	pthread_t		master;
	int				*forks;		// maybe remove - but useful for visualize
	pthread_mutex_t	*mutex;
}				t_monastery;

// -------------------------------------------------------------------- PARSING
int		parse_monastery(t_monastery *data, char **argv);

// -------------------------------------------------------------------- THREADS
int		create_threads(t_monastery *data);
int		join_threads(t_monastery *data);
void	*routine(void *arg);
void	*supervision(void *arg);

// ----------------------------------------------------------------------- TIME
uint64_t	get_time_ms(void);					// return time in milliseconds
uint64_t	get_time_us(void);					// return time in microsecond
// uint64_t	get_rel_time_ms(uint64_t start);	// return time in ms, relative to the beginning of program
void		better_sleep(uint64_t n);

// ---------------------------------------------------------------------- UTILS
int		ft_atoi(const char *str);
void	*ft_calloc(size_t len, size_t n_bits);

// ---------------------------------------------------------------- PRINT UTILS
int		error(int err_code, char *file, int line);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	print_single_philo(t_philo *philo);
void	print_all_philo(t_philo **philo);

#endif
