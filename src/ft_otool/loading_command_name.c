/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_command_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:33:13 by gemaroul          #+#    #+#             */
/*   Updated: 2020/11/12 17:33:15 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/loading_command_name.h"

const t_lc	*g_loading_commands_table_infos(void)
{
	return (g_loading_commands_table);
}

const t_lc	*lc_info_from_id(uint32_t id)
{
	const t_lc *lci;

	lci = g_loading_commands_table;
	while (lci->cmd_name != NULL)
	{
		if (lci->cmd == id)
			return (lci);
		lci++;
	}
	return (NULL);
}
