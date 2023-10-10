/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:55:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/10 11:10:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>	// printf
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
	// dead flag
}				t_time;

typedef struct s_shared
{
	int				n_eat;
	int				last_eat_time;
	int				*dead_flag;
	pthread_mutex_t	*l_fork;			// mut excl of the forks
	pthread_mutex_t	*r_fork;			// mut excl of the forks
	pthread_mutex_t	*print_lock;		// mut excl when print messages
	pthread_mutex_t	*eat_lock;			// mut excl when update/read last_time_eat (persnoal)
	pthread_mutex_t	*dead_lock;			// mut excl to update/read if someone is dead
}			t_shared;

typedef struct s_philo
{
	// private resources
	int				id;
	pthread_t		th;
	struct s_time	time;				// every philo has its own, so no need of mutex
	// time was a pointer to monastery
	int				starting_group;

	// shared resources with monitors
	int				last_eat_time;
	int				n_eat;				// n of times the philo eats
	int				*dead_flag;
	pthread_mutex_t	*l_fork;			// mut excl of the forks
	pthread_mutex_t	*r_fork;			// mut excl of the forks
	pthread_mutex_t	*print_lock;		// mut excl when print messages
	pthread_mutex_t	*eat_lock;			// mut excl when update/read last_time_eat (persnoal)
	pthread_mutex_t	*dead_lock;			// mut excl to update/read if someone is dead
}				t_philo;

typedef struct s_monastery
{
	// private resources
	int				n_philo;
	struct s_philo	*philo; // **philo
	struct s_time	time;

	pthread_t		th_dead_monitor;
	pthread_t		th_eat_monitor;


	// shared
	int				dead_flag;
	int				*n_eat_status;		// n of times each philo has eaten
	pthread_mutex_t	*forks;				// n of mutex == n_philo
	pthread_mutex_t	print_lock;			// mut excl when print messages (shared between all)
	pthread_mutex_t	*eat_locks;			// mut excl when update/read last_time_eat (shared between monitor and philo)
	pthread_mutex_t	dead_lock;			// mut excl to update/read if someone is dead

	// errors
	int				err_code;
}				t_monastery;

// -------------------------------------------------------------------- PARSING
int		create_monastery(t_monastery *data, char **argv);
t_philo	*create_philo(t_monastery *data);

// -------------------------------------------------------------------- THREADS
int		create_threads(t_monastery *data);
int		join_threads(t_monastery *data);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	*eat_routine(void *arg);

// ----------------------------------------------------------------------- TIME
int64_t	get_abs_time(void);
int64_t	get_rel_time(int64_t clock_start);
void	accurate_sleep_ms(int64_t n);

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
void	print_all_philo(t_monastery *data);
void	print_tmstmp(t_philo *philo, t_action what, int64_t when);

#endif
