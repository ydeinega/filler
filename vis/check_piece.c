/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:51:29 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/05 15:51:46 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	check_column(t_brd *piece, int i)
{
	int j;

	j = 0;
	while (i < piece->i)
	{
		while (j < piece->j)
		{
			if (piece->brd[i][j] == '*')
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static int	check_row(t_brd *piece, int i, int j)
{
	while (j < piece->j)
	{
		if (piece->brd[i][j] == '*')
			return (0);
		j++;
	}
	return (1);
}

int			check_piece(t_filler *game, t_brd *brd, t_brd *pc, t_coord p)
{
	int i;
	int j;
	int touch;

	i = -1;
	j = -1;
	touch = 0;
	while (++i < pc->i && p.i + i < brd->i)
	{
		while (++j < pc->j && p.j + j < brd->j)
		{
			if (pc->brd[i][j] == '*' &&
				brd->brd[p.i + i][p.j + j] == game->player.me)
			{
				touch++;
				game->touch = p;
			}
			else if (pc->brd[i][j] == '*' && brd->brd[p.i + i][p.j + j] != '.')
				return (0);
		}
		if (!check_row(pc, i, j))
			return (0);
		j = -1;
	}
	return (touch == 1 && check_column(pc, i) ? 1 : 0);
}
