#include "codexion.h"

void	take_dongles(t_coder *coder, t_data *data)
{
	if (coder->left < coder->right)
	{
		dongle_acquire(coder->left, data);
		log_msg(data, coder->id, "has taken a dongle");
		dongle_acquire(coder->right, data);
		log_msg(data, coder->id, "has taken a dongle");
	}
	else
	{
		dongle_acquire(coder->right, data);
		log_msg(data, coder->id, "has taken a dongle");
		dongle_acquire(coder->left, data);
		log_msg(data, coder->id, "has taken a dongle");
	}
}

void	dongle_acquire(t_dongle *dongle, t_data *data)
{
	pthread_mutex_lock(&dongle->mutex);
	while (dongle->in_use && !stopped(data))
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
    if (stopped(data))
    {
        pthread_mutex_unlock(&dongle->mutex);
        pthread_exit(NULL);
    }
	dongle->in_use = 1;
	pthread_mutex_unlock(&dongle->mutex);
}

void	dongle_release(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->in_use = 0;
	pthread_mutex_unlock(&dongle->mutex);
	pthread_cond_signal(&dongle->cond);
}