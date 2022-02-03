/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:43:47 by lubov             #+#    #+#             */
/*   Updated: 2022/02/03 22:43:47 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_input_data(int argc,char **argv)
{
	int i;

	i = 1;
	if (argc < 5 || argc > 7)
	{
		printf("Invalid number of input arguments");
		return (1);
	}
	while(argv[i])
	{
		if(!(ft_isnumb(argv[i]) && ft_atoi(argv[i])))
		{
			printf("Invalid input arguments(should only be numbers)");
			return (1);
		}  
		i++;
	}
		return (0);   
}

void init_input_args(t_arg *input_args, int argc, char **argv)
{
	input_args->number_of_philo = ft_atoi(argv[1]);
	input_args->time_to_die = ft_atoi(argv[2]);
	input_args->time_to_eat = ft_atoi(argv[3]);
	input_args->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
	{
		input_args->number_eat = ft_atoi(argv[5]);
	}
	 
}
long get_time(void)
{
	struct timeval	time;
	long			res;

	gettimeofday(time, NULL);
	res = 1000 * time.tv_sec + time.tv_usec / 1000;
	return(res);
}

void philo_process(void * data)
{
	t_philo *philo;
	long	start;

	philo = (t_philo *)data;
	start = get_time();


}

void init_thread(t_arg *input_args)
{
	pthread_t	*tr;
	int			n;

	tr = malloc(sizeof(pthread_t) * input_args->number_of_philo);
	n = input_args->number_of_philo;
	if(!tr)
		exit(0);
	while( n != 0)
	{
		pthread_create(tr[n - 1], NULL, philo_process, (void *)input_args->data_philo);
		n--;
	}
	pthread_join(tr, NULL);

}

void init_mutex (t_arg *input_args)
{
	pthread_mutex_t	*mutex;
	int				n;

	mutex = malloc(sizeof(pthread_mutex_t) * input_args->number_of_philo);
	if(!mutex)
		exit(0);
	n = input_args->number_of_philo;
	while( n >= 0)
	{
		pthread_mutex_init(&mutex[n], NULL);
		n--;
	}
	input_args->forks = mutex;    
}

void init_philo(t_arg *input_data)
{
	t_philo	*philo;
	int		i;
	int		n;

	i = 0;
	n = input_data->number_of_philo;
	philo = malloc(sizeof(t_philo) * n);
	if(!philo)
		exit(0);
	while (i < n)
	{
		philo[i].philo_id = i;
		philo[i].time_to_die = input_data->time_to_die;
		philo[i].time_to_eat = input_data->time_to_eat;
		philo[i].time_to_sleep = input_data->time_to_sleep;
		if(i == 0 || i == (n - 1))
		{
			if(i == 0)
			{
				philo->l_fork = &input_data->forks[n - 1];
				philo->r_fork = &input_data->forks[i];
			}
			philo->l_fork = &input_data->forks[i];
			philo->r_fork = &input_data->forks[0];
		}
		philo->l_fork = &input_data->forks[i - 1];
		philo->r_fork = &input_data->forks[i];
		i++;
	}
}
int main(int argc, char **argv)
{
	t_arg input_args;

	if(check_input_data(argc,argv))
		return (1); 
	init_input_args(&input_args, argc, argv);
	init_mutex(&input_args);
	init_philo(&input_args);
}
