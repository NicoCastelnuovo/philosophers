/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:55:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/11 17:46:14 by ncasteln         ###   ########.fr       */
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
# include <libc.h>		// memset

# define EARGC				1
# define EMALLOC			2
# define ECREATE_THREAD		3
# define ETHJOIN			4
# define EMUTEX				5
# define ECREATE_PHILO		6

typedef struct s_philo
{
	int				id;
	int				*l_fork;
	int				*r_fork;
	int				die;
	int				eat;
	int				sleep;
	int				end;
	pthread_mutex_t	*mutex;
	int				*n;
}				t_philo;

typedef struct s_monastery
{
	int				n_philo;	// total n of philo/forks
	pthread_t		*th;		// ptr to the threads
	struct s_philo	**philo;	// ptr to the philosophers
	int				*forks;		// ptr to the forks
	pthread_mutex_t	mutex;
}				t_monastery;

// -------------------------------------------------------------------- PARSING
void	parse_argv(int id, t_philo *philo, char **argv);

// -------------------------------------------------------------------- JOIN_TH
int		create_threads(t_monastery *data);
int		join_threads(t_monastery *data);


// ----------------------------------------------------------------------- TIME
long int	get_ms(void);

// ---------------------------------------------------------------------- UTILS
int		ft_atoi(const char *str);
void	*ft_calloc(size_t len, size_t n_bits);

// ---------------------------------------------------------------- PRINT UTILS
int		error(int err_code, char *file, int line);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	print_state(t_philo *philo);

#endif
