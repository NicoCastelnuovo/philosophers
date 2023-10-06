/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:55:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/06 11:57:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>	// printf()
# include <sys/time.h>
# include <stdio.h>
# include <string.h>	// memset used in ft_calloc
// # include <libc.h>	// memset used in ft_calloc

// error definitions
# define EARGC				1
# define EMALLOC			2
# define ECREATE_THREAD		3
# define ETHJOIN			4
# define EMUTEX_INIT		5
# define EMUTEX_DESTROY		6
# define ECREATE_PHILO		7
# define EGET_TIME			8

// action definition
typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK
}			t_action;

typedef struct s_time
{
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			eat_limit;
	int64_t		clock_start;			// to be intended like the internal clock
	int			dead_flag;
}				t_time;

typedef struct s_philo
{
	int				id;
	pthread_t		th;
	struct s_time	*time;
	int				eat_time;
	int				starting_group;		// [1] start - [0] queued
	int				n_eat;				// n of times the philo eats
	pthread_mutex_t	*l_fork;			// mut excl of the forks
	pthread_mutex_t	*r_fork;			// mut excl of the forks
	pthread_mutex_t	*print_lock;		// mut excl when print messages
	pthread_mutex_t	*eat_lock;			// mut excl when update/read last_time_eat (persnoal)
	pthread_mutex_t	*dead_lock;			// mut excl to update/read if someone is dead
}				t_philo;

typedef struct s_monastery
{
	// philos
	int				n_philo;
	struct s_philo	**philo;
	struct s_time	*time;

	// dead monitor
	pthread_t		th_dead_monitor;

	// eat monitor
	pthread_t		th_eat_monitor;
	int				*n_eat_status;	// n of times each philo has eaten

	// mutexes
	pthread_mutex_t	*forks;			// n of mutex == n_philo
	pthread_mutex_t	print_lock;		// mut excl when print messages (shared between all)
	pthread_mutex_t	*eat_locks;		// mut excl when update/read last_time_eat (shared between monitor and philo)
	pthread_mutex_t	dead_lock;		// mut excl to update/read if someone is dead

	// errors
	int				err_code;
}				t_monastery;

// -------------------------------------------------------------------- PARSING
int		create_monastery(t_monastery *data, char **argv);
t_philo	**create_philo(t_monastery *data);

// -------------------------------------------------------------------- THREADS
int		create_threads(t_monastery *data);
int		join_threads(t_monastery *data);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	*eat_routine(void *arg);

// ----------------------------------------------------------------------- TIME
int64_t	get_time_ms(void);
int64_t	get_time_us(void);
int64_t	now_ms(int64_t clock_start);
int64_t	now_us(int64_t clock_start);
void	accurate_sleep_ms(int64_t n);
void	accurate_sleep_us(int64_t time);

// ---------------------------------------------------------------------- UTILS
int		ft_atoi(const char *str);
void	*ft_calloc(size_t len, size_t n_bits);

// ---------------------------------------------------------------- PRINT UTILS
int		error(int *err_store, int err_code, char *file, int line);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	print_single_philo(t_philo *philo);
void	print_all_philo(t_philo **philo);
void	print_tmstmp(t_philo *philo, t_action what, int64_t when);

#endif
