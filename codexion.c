#include "codexion.h"

void	*coder_thread(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->thread_data;
	take_dongles(coder, data);
	coder->last_compile_start = diff_ms(&data->start_time);
	log_msg(data, coder->id, "is compiling");
	usleep(data->params.compile * 1000);
	dongle_release(coder->left);
	dongle_release(coder->right);
	log_msg(data, coder->id, "is debugging");
	usleep(data->params.debug * 1000);
	log_msg(data, coder->id, "is refactoring");
	usleep(data->params.refactor * 1000);
	return (NULL);
}

static void	destroy_dongles(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_coders)
	{
		pthread_mutex_destroy(&data->dongles[i].mutex);
		pthread_cond_destroy(&data->dongles[i].cond);
    	i++;
	}
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (!parser(argc, argv, &params))
		return (1);
	if (!create_data(&data, &params))
		return (1);
	gettimeofday(&data.start_time, NULL);
	pthread_mutex_init(&data.log_mutex, NULL);
	data.stop = 0;
	pthread_mutex_init(&data.stop_mutex, NULL);
	pthread_create(&monitor, NULL, monitor_thread, &data);
	i = 0;
	while (i < params.num_coders)
	{
		data.coders[i].thread_data = &data;
		pthread_create(&data.coders[i].thread, NULL, coder_thread, &data.coders[i]);
		i++;
	}
	i = 0;
	while (i < params.num_coders)
	{
		pthread_join(data.coders[i].thread, NULL);
		i++;
	}
	request_stop(&data);
	pthread_join(monitor, NULL);
	destroy_dongles(&data);
	pthread_mutex_destroy(&data.log_mutex);
	pthread_mutex_destroy(&data.stop_mutex);
	free(data.coders);
	free(data.dongles);
	return (0);
}