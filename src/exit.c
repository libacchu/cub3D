/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: libacchu <libacchu@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:38:39 by libacchu          #+#    #+#             */
/*   Updated: 2023/01/09 14:07:24 by libacchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_exit(char *str, t_cub3D *game)
{
	if (str)
		ft_putstr_fd(str, 2);
	ft_free(game);
	exit(0);
}