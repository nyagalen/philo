/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:58:46 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/22 18:39:49 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	int				meals;
	int				eating;
	long long		start_meal;
	struct s_data	*data;	
}	t_philo;

typedef struct s_data
{
	long			nb_philo;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
	int				dead_ph;
	pthread_mutex_t	print_m;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	dead_m;	
	t_philo			*philos;
}	t_data;

int			check_args(char **argv);
void		init_data(t_data *data, int argc, char **argv);
int			ft_atoi(char *num);
long long	ft_atoll(char *num);
long long	get_time(void);
void		init_forks(pthread_mutex_t *forks, int ph_num);
void		init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks);
void		print(t_philo *philo, char *str);
void		destroy(char *str, t_data *data, pthread_mutex_t *forks);
void		ft_usleep(long long ms);
void		activate_threads(t_philo *philos, pthread_mutex_t *forks,
				int nb_ph);
void		*routine(void *ph);
void		think(t_philo *ph);
void		zzz(t_philo *ph);
void		eat(t_philo *ph);
void		*monitor(void *pointer);
int			dead_detected(t_philo *philos);
int			rip(t_philo *philo);
int			dead(t_data *data);
int			all_ate(t_philo *philos);

#endif
