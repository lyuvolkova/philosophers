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
        if(!(ft_digit(argv[i]) && ft_atoi(argv[i]))
        {
        printf("Invalid input arguments(should only be numbers)");
        return (1);
        }  
        i++;
    }
        return (0);   
}

int main(int argc, char **argv)
{
    if(check_input_data(argc,argv))
        return(1);
    init_philosophers();
}
