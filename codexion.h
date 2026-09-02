#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_params
{
	int		num_coders;
	long	burnout;
	long	compile;
	long	debug;
	long	refactor;
	int		required;
	long	cooldown;
	char	*scheduler;
}	t_params;

typedef struct s_dongle
{
	int				in_use;        // 0 = свободен, 1 = занят
	pthread_mutex_t	mutex;         // ключ, защищающий in_use
	pthread_cond_t	cond;          // "будильник" для тех, кто ждёт
	long			cooldown;   // когда освободили (для cooldown)
}	t_dongle;

typedef struct s_coder
{
	int			id;
	pthread_t	thread;
	t_dongle	*left;
	t_dongle	*right;
	long		last_compile_start;
	int			compiles_done;
	t_data		*thread_data;
}	t_coder;

typedef struct s_data
{
	t_params		params;
	t_coder			*coders;
	t_dongle		*dongles;
	struct timeval	start_time;
	pthread_mutex_t	log_mutex;
	int				stop;
	pthread_mutex_t stop_mutex;
}	t_data;

int	parser(int ac, char **av, t_params *params);
long	parse_long(const char *s, int *ok);
int	parse_av1_2(char **av, t_params *p);
int	parse_av3_4(char **av, t_params *p);
int	parse_av5_6(char **av, t_params *p);
int	parse_av7_8(char **av, t_params *p);

int	create_data(t_data *data, t_params *params);

void	log_msg(t_data *data, int coder_id, char *message);
long	diff_ms(struct timeval *start);

void	take_dongles(t_coder *coder, t_data *data);
void	dongle_acquire(t_dongle *dongle, t_data *data);
void	dongle_release(t_dongle *dongle);

void	*monitor_thread(void *arg);
int		stopped(t_data *data);
void	request_stop(t_data *data);

#endif