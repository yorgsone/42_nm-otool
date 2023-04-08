#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include "../libft.h"
# define E_INVALID_OPT -1
# define E_EOF -2
# define E_INVALID_OPTSTR -3
# define E_EOO -4
# define E_NO_OPTION_AFTER_DASH -5

int ft_getopt(int argc, char *const argv[], const char *optstring);

#endif