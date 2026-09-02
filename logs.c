#include "codexion.h"

long	diff_ms(struct timeval *start)
{
	struct timeval	now;
	long			sec_diff;
	long			usec_diff;

	gettimeofday(&now, NULL);
	sec_diff = now.tv_sec - start->tv_sec;
	usec_diff = now.tv_usec - start->tv_usec;
	return (sec_diff * 1000 + usec_diff / 1000);
}

void	log_msg(t_data *data, int coder_id, char *mes)
{
	pthread_mutex_lock(&data->log_mutex);
	printf("%ld %d %s\n", diff_ms(&data->start_time), coder_id, mes);
	pthread_mutex_unlock(&data->log_mutex);
}