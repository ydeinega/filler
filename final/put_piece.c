/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:30:41 by ydeineha          #+#    #+#             */
/*   Updated: 2018/05/22 14:30:44 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		put_piece(t_brd *board, t_brd **piece, int player)
{
	t_filler	*game;
	int			i;
	int			j;

	i = -1;
	j = -1;
	if ((game = create_game(player)) != NULL)
	{
		while (++i < board->i)
		{
			while (++j < board->j)
			{
				game->tmp.i = i;
				game->tmp.j = j;
				if (check_piece(game, board, *piece, game->tmp))
					check_min(game, board);
			}
			j = -1;
		}
	}
	ft_printf("%i %i\n", game->point.i, game->point.j);
	clean_board(piece);
	free(game);
}

void		check_min(t_filler *game, t_brd *board)
{
	int		i;
	int		j;
	t_coord	pt;

	i = -1;
	j = -1;
	while (++i < board->i)
	{
		while (++j < board->j)
		{
			if (board->brd[i][j] == game->player.enemy)
			{
				pt.i = i;
				pt.j = j;
				if (game->min < 0 || (game->min >= 0
					&& game->min > dst_mnh(pt, game->touch)))
				{
					game->min = dst_mnh(pt, game->touch);
					game->point = game->tmp;
				}
			}
		}
		j = -1;
	}
}

t_filler	*create_game(int player)
{
	t_filler	*game;

	game = (t_filler *)malloc(sizeof(t_filler));
	if (!game)
		return (NULL);
	game->player.me = player == 1 ? 'O' : 'X';
	game->player.enemy = player == 1 ? 'X' : 'O';
	game->point.i = 0;
	game->point.j = 0;
	game->min = -1;
	return (game);
}

int			dst_mnh(t_coord a, t_coord b)
{
	int i_sum;
	int	j_sum;

	i_sum = a.i >= b.i ? a.i - b.i : b.i - a.i;
	j_sum = a.j >= b.j ? a.j - b.j : b.j - a.j;
	return (i_sum + j_sum);
}
