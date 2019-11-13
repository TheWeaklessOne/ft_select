/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_strucrutes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:02:20 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/08 18:02:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/data_structures.h"

void		on_crash(int crash)
{

	if (crash == MALLOC_ERR)
		write(2, "Malloc error\n", 13);
	if (crash == ENV_ERR)
		write(2, "Environment error\n", 18);
	exit(crash);
}
