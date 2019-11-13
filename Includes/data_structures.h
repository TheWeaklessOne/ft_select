/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:03:30 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/08 18:03:31 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

# include <stdlib.h>
# include <unistd.h>

# include "list.h"

enum		e_crash
{
	MALLOC_ERR = 1,
	ENV_ERR
};

void		on_crash(int crash);

#endif
