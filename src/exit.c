/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:38:39 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/14 14:07:47 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	ft_exit(char *str, t_cub3D *game)
{
	(void)game;
	if (str)
		ft_putstr_fd(str, 2);
	//ft_free(game);
	exit(0);
}
