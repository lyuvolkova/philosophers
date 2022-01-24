#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_isnumb(char *s)
{
	while(*s)
	{
		if(!ft_isdigit(*s))
			return(0);
		s++;	
	}
	return(1);
}

int	ft_isspace(int c)
{
	if (c == 32 || c == 9 || c == 10 ||c == 11 ||\
		c == 12 || c == 13)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		num;
	int		minus;

	i = 0;
	num = 0;
	minus = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-' )
			minus = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (int)str[i] - 48;
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (num * minus);
}
