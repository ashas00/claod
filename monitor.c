#include "codexion.h"

int	stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->stop_mutex);
	stopped = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stopped);
}

void	request_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

static void	wake_all_dongles(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_coders)
	{
		pthread_mutex_lock(&data->dongles[i].mutex);
		pthread_cond_broadcast(&data->dongles[i].cond);
		pthread_mutex_unlock(&data->dongles[i].mutex);
		i++;
	}
}

static void	check_burnout(t_data *data, long now)
{
	t_coder	*coder;
	int		i;

	i = 0;
	while (i < data->params.num_coders)
	{
		coder = &data->coders[i];
		if (now - coder->last_compile_start >= data->params.burnout)
		{
			log_msg(data, coder->id, "burned out");
			request_stop(data);
			wake_all_dongles(data);
			return ;
		}
		i++;
	}
}

void	*monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!stopped(data))
	{
		check_burnout(data, diff_ms(&data->start_time));
		usleep(5000);
	}
	return (NULL);
}