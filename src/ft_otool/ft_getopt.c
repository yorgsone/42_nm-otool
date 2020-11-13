/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:32:58 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:33:01 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_getopt.h"

int	g_optind = 1;
int	g_optcol = 1;
int	g_optopt = '?';
int	g_opterr = 1;

static int	is_valid_optstring(const char *s)
{
	while (*s)
	{
		if (!ft_isalpha(*s))
			return (-1);
		s++;
	}
	return (1);
}

static int	get_opt(const char *s, const char *opts)
{
	int i;

	i = 0;
	if (!*s || !*opts)
		return (-1);
	while (opts[i])
	{
		if (*s == opts[i])
			return (opts[i]);
		i++;
	}
	ft_printf("Illegal option: -%c\n", *s);
	return (E_INVALID_OPT);
}

static int	check_opterr(int argc, char c)
{
	if (g_optind >= argc)
	{
		g_opterr = E_EOF;
		return (E_EOF);
	}
	else if (c != '-')
	{
		g_opterr = E_EOO;
		return (E_EOO);
	}
	return (1);
}

int			ft_getopt(int argc, char *const argv[], const char *optstring)
{
	int	opt;

	opt = E_INVALID_OPT;
	if (check_opterr(argc, argv[g_optind][0]) != 1)
		return (g_opterr);
	if (g_opterr == E_EOF || g_opterr == E_EOO
	|| g_optind >= argc || argv[g_optind][0] != '-' || !optstring)
		return (opt);
	else if (g_optcol >= (int)ft_strlen(argv[g_optind]))
	{
		g_optind++;
		g_optcol = 1;
		return (ft_getopt(argc, argv, optstring));
	}
	if (!is_valid_optstring(optstring))
	{
		g_opterr = E_INVALID_OPTSTR;
		return (E_INVALID_OPTSTR);
	}
	opt = get_opt(&argv[g_optind][g_optcol++], optstring);
	if (opt != -1)
		g_optopt = opt;
	else
		g_opterr = E_INVALID_OPT;
	return (opt);
}
