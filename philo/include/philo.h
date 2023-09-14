/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:55:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/14 13:47:57 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>	// printf()
# include <sys/time.h>
# include <errno.h>
# include <stdio.h>
# include <libc.h>		// memset used in ft_calloc

// error definitions
# define EARGC				1
# define EMALLOC			2
# define ECREATE_THREAD		3
# define ETHJOIN			4
# define EMUTEX				5
# define ECREATE_PHILO		6
# define EGET_TIME			7

// action definition
typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}			t_action;

typedef struct s_time
{
	int			to_die;
	int			to_eat;			// add to_ for readability ???
	int			to_sleep;
	int			limit;
	int64_t		clock_start;	// to be intended like the internal clock
	int			is_end;
}				t_time;

typedef struct s_philo
{
	int				id;			// set to -1 if die
	struct s_time	*time;
	int				last_eat;
	int				start_sleeping;
	int				end_sleeping; /// remove ?????
	int				start_thinking;
	int				end_thinking;
	int				is_turn;	// [0] start - [1] queued // still necessary ???
	int				n_cycles;
	int				*fork[2];	// maybe remove
	pthread_mutex_t	*mutex[2];	// change to fork ????
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

int		create_monastery(t_monastery *data, char **argv);
t_philo	**create_philo(t_monastery *data);

// -------------------------------------------------------------------- THREADS

int		create_threads(t_monastery *data);
int		join_threads(t_monastery *data);
void	*routine(void *arg);
void	*supervision(void *arg);

// ----------------------------------------------------------------------- TIME

int64_t		get_time_ms(void);
int64_t		now(int64_t clock_start);
void		better_sleep(int64_t n);

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
void	print_tmstmp(int who, t_action what, int64_t clock_start);

#endif
