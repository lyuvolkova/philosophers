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
        if(!(ft_isnumb(argv[i]) && ft_atoi(argv[i]))
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

void init_mutex (t_arg *input_args)
{
    pthread_mutex_t *mutex;
    int n;

    mutex = malloc(sizeof(pthread_mutex_t) * input_args->number_of_philo);
    if(!mutex)
        exit(0);
    n = input_args->number_of_philo;
    while( n >= 0)
    {
        pthread_mutex_init(&mutex[n], NULL);
        n--;
    }    
        

    
}

int main(int argc, char **argv)
{
    t_arg input_args;

    if(check_input_data(argc,argv))
        return (1); 
    init_input_args(&input_args, argc, argv);
}
