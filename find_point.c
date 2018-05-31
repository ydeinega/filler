/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 13:36:34 by ydeineha          #+#    #+#             */
/*   Updated: 2018/05/31 13:36:37 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_coord	find_point(t_filler *game, t_brd *board, t_brd *piece)
{
	int		min;
	int		i;
	int		j;
	t_coord	point;
	t_coord	tmp;

	min = -1;
	i = -1;
	j = -1;
	while (++i < board->i)
	{
		while (++j < board->j)
		{
			tmp.i = i;
			tmp.j = j;
			if (check_piece(game, board, piece, tmp))
			{
				ft_printf("tmp = (%i, %i)\n", tmp.i, tmp.j);
				ft_printf("min = %i\n", min);
				if (min < 0 || (min >= 0 && (min > dst_mnh(tmp, game->goal1)
					|| min > dst_mnh(tmp, game->goal2))))
				{
					ft_printf("I'm here\n");
					min = dst_mnh(tmp, game->goal1) < dst_mnh(tmp, game->goal2) ?
					dst_mnh(tmp, game->goal1) : dst_mnh(tmp, game->goal2);
					point = tmp;
					ft_printf("point = (%i, %i)\n", point.i, point.j);
					ft_printf("min = %i\n\n", min);
				}
			}
		}
		j = -1;
	}
	return (point);
}

int		check_piece(t_filler *game, t_brd *board, t_brd *piece, t_coord pt)
{
	int i;
	int j;
	int touch;
	int start;

	i = -1;
	j = -1;
	touch = 0;
	start = pt.j;
	while (pt.i < board->i && ++i < piece->i)
	{
		while (pt.j < board->j && ++j < piece->j)
		{
			if (board->brd[pt.i][pt.j] == game->player.me)
				touch++;
			if (touch > 1 || board->brd[pt.i][pt.j] == game->player.enemy)
				return (0);
			pt.j++;
		}
		if (j != piece->j)
			return (0);
		j = 0;
		pt.j = start;
		pt.i++;
	}
	return (pt.i == piece->i && touch == 1 ? 1 : 0);
}
