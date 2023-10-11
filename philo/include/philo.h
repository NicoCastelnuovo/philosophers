/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:55:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 15:51:09 by ncasteln         ###   ########.fr       */
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

// error definitions
# define EARG				1
# define EMALLOC			2
# define ECREATE_THREAD		3
# define ETHJOIN			4
# define EMUTEX_INIT		5
# define EMUTEX_DESTROY		6
# define ECREATE_PHILO		7
# define EGET_TIME			8

typedef enum e_action
{
	FORK,
	EAT,
	SLEEP,
	THINK,
}			t_action;

// timetable informations
typedef struct s_ttable
{
	int			to_die;
	int			to_eat;
	int			to_sleep;
	int			to_think;
	int			eat_limit;
	int64_t		clock_start;
}				t_ttable;

/*
	Since the philos may not communicate between each other, each one has
	no access to the info hold by the others.
	@param pthread_mutex_t	*print_lock - mutex for printing
	@param pthread_mutex_t	*eat_time_lock - mutex for last_eat_time
	@param pthread_mutex_t	*meals_lock - mutex for n_meals
	@param pthread_mutex_t	*end_lock - mutex for eng_flag
*/
typedef struct s_philo
{
	int				id;
	pthread_t		th;
	struct s_ttable	*time;
	int				last_eat_time;
	int				n_meals;
	int				*end_flag;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*eat_time_lock;
	pthread_mutex_t	*meals_lock;
	pthread_mutex_t	*end_lock;
}				t_philo;

typedef struct s_monastery
{
	int				n_philo;
	struct s_philo	*philo;
	struct s_ttable	time;
	pthread_t		dead_monitor;
	pthread_t		meal_monitor;
	int				end_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*eat_time_locks;
	pthread_mutex_t	*meals_locks;
	pthread_mutex_t	end_lock;
	int				err_code;
}				t_monastery;

// -------------------------------------------------------------------- PARSING
int		create_monastery(t_monastery *data, int argc, char **argv);
t_philo	*create_philo(t_monastery *data);

// ---------------------------------------------------------------------- MUTEX
int		create_locks(t_monastery *data);
int		destroy_mutex(t_monastery *data);

// -------------------------------------------------------------------- THREADS
int		create_threads(t_monastery *data);
int		join_threads(t_monastery *data);
void	*philo_routine(void *arg);
void	*death_monitor(void *arg);
void	*eat_routine(void *arg);

// ----------------------------------------------------------------------- TIME
int64_t	get_abs_time(void);
int64_t	get_rel_time(int64_t clock_start);
void	accurate_sleep_ms(int64_t n);

// ---------------------------------------------------------------------- UTILS
long	ft_atol(char *str);
void	*ft_calloc(size_t len, size_t n_bits);
void	free_mem(t_monastery *data);

// ---------------------------------------------------------------- PRINT UTILS
int		error(int *err_store, int err_code);
void	print_all_philo(t_monastery *data);
void	print_tmstmp(t_philo *philo, t_action what, int64_t when);

#endif
