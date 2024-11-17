/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:11:25 by akloster          #+#    #+#             */
/*   Updated: 2024/11/17 21:08:28 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>

# ifdef __linux__
#  define TAKE_FORK "%ld %d has taken a fork\n"
#  define EAT "%ld %d is eating\n"
#  define SLEEP "%ld %d is sleeping\n"
#  define THINK "%ld %d is thinking\n"
#  define DIE "%ld %d died\n"
# elif __APPLE__
#  define TAKE_FORK "%ld %d has taken a fork\n"
#  define EAT "%ld %d is eating\n"
#  define SLEEP "%ld %d is sleeping\n"
#  define THINK "%ld %d is thinking\n"
#  define DIE "%ld %d died\n"
# endif
# define MAX_USEC 999999
# define NEED_SLEEP true
# define NO_SLEEP false
# define MAX_PHILO 200

typedef struct s_data
{
	int				*ids;
	int				n_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				n_orbit;
	long			time_start;
	bool			ready;
	bool			stop;
	pthread_t		*philo;
	long			*elapsed;
	pthread_t		check_routine;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*read;
	pthread_mutex_t	*write;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*ready_lock;
	pthread_mutex_t	*rw_lock;
	pthread_mutex_t	*stop_lock;
}	t_data;

typedef struct s_table
{
	t_data			*data;
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*ready_lock;
	pthread_mutex_t	*stop_lock;
}	t_table;

void	put_str(char *str, int fd);
int		ft_error(char *msg);
void	init_table(t_data *data, t_table *table);
int		parsing(char **av, t_data *data);
int		ft_mod_atoi(char *str);
bool	ft_compare(char *s1, char *s2);
void	my_free(t_data *data);
int		alloc_threads(t_data *data);
int		init_philo(t_data *data);
void	*philo_routine(void *data);
void	kill_mutex(t_data *data);
long	ft_gettime(void);
void	set_forks(t_table *table, int n_philo);
bool	get_stop_bool(t_data *data);
void	philo_eat(t_table *table);
void	philo_sleep(t_table *table);
void	*check_routine(void *ptr);
void	print_msg(t_data *data, char *msg, int id);
void	ft_usleep(long time);

#endif
