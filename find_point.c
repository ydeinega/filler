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
	int			i;
	int			j;
	int			min;
	t_coord		point;
	t_coord		tmp;

	min = -1;
	i = -1;
	j = -1;
	point.i = 0;
	point.j = 0;
	// ft_printf("count = %i\n", game->count);
	// ft_printf("goal1 = (%i, %i)\n", game->goal1.i, game->goal1.j);
	// ft_printf("goal2 = (%i, %i)\n", game->goal2.i, game->goal2.j);
	while (++i < board->i)
	{
		while (++j < board->j)
		{
			tmp.i = i;
			tmp.j = j;
			if (check_piece(game, board, piece, tmp))
				set_point(game, tmp, &point, &min);
		}
		j = -1;
	}
	if (game->count == 0)
		set_count(game, board, piece, point);
	// ft_printf("min = %i\n", min);
	return (point);
}

void	set_point(t_filler *game, t_coord tmp, t_coord *point, int *min)
{
	// ft_printf("count = %i\n", game->count);
	// ft_printf("goal1 = (%i, %i)\n", game->goal1.i, game->goal1.j);
	// ft_printf("goal2 = (%i, %i)\n", game->goal2.i, game->goal2.j);
	if (game->count == 0)
	{
		if (*min < 0 || (*min >= 0 && (*min > dst_mnh(tmp, game->goal1)
		|| *min > dst_mnh(tmp, game->goal2))))
		{
			*min = dst_mnh(tmp, game->goal1) < dst_mnh(tmp, game->goal2) ?
			dst_mnh(tmp, game->goal1) : dst_mnh(tmp, game->goal2);
			*point = tmp;
			// set_count(game, *point);
		}
	}
	else if (game->count == 1)
	{
		if (*min < 0 || (*min >= 0 && *min > dst_mnh(tmp, game->goal1)))
		{
			*min = dst_mnh(tmp, game->goal1);
			*point = tmp;
		}
	}
	else if (game->count == 2)
	{
		if (*min < 0 || (*min >= 0 && *min > dst_mnh(tmp, game->goal2)))
		{
			*min = dst_mnh(tmp, game->goal2);
			*point = tmp;
		}
	}
	// ft_printf("min = %i\n", *min);
}

void	set_count(t_filler *game, t_brd *board, t_brd *piece, t_coord pt)
{
	int i;
	int j;
	int start;

	i = 0;
	j = 0;
	start = pt.j;
	while (pt.i < board->i && i < piece->i)
	{
		while (pt.j < board->j && j < piece->j)
		{
			if (piece->brd[i][j] == '*')
			{
				if (check_count(game, pt))
					break ;				
			}
			pt.j++;
			j++;
		}
		j = 0;
		pt.j = start;
		i++;
		pt.i++;
	}
}

int		check_count(t_filler *game, t_coord point)
{
	if ((game->goal1.i == 0 || game->goal1.i == game->size.i - 1)
		&& point.i == game->goal1.i && dst_mnh(point, game->goal2) >=
		dst_mnh(game->goal1, game->goal2))
		game->count = 2;
	else if ((game->goal1.j == 0 || game->goal1.j == game->size.j - 1)
		&& point.j == game->goal1.j && dst_mnh(point, game->goal2) >=
		dst_mnh(game->goal1, game->goal2))
		game->count = 2;
	else if ((game->goal2.i == 0 || game->goal2.i == game->size.i - 1)
		&& point.i == game->goal2.i && dst_mnh(point, game->goal1) >=
		dst_mnh(game->goal1, game->goal2))
		game->count = 1;
	else if ((game->goal2.j == 0 || game->goal2.j == game->size.j - 1)
		&& point.j == game->goal2.j && dst_mnh(point, game->goal1) >=
		dst_mnh(game->goal1, game->goal2))
		game->count = 1;
	return (game->count);
}

int		check_piece(t_filler *game, t_brd *board, t_brd *piece, t_coord pt)
{
	int i;
	int j;
	int touch;
	int start;

	i = 0;
	j = 0;
	touch = 0;
	start = pt.j;
	while (pt.i < board->i && i < piece->i)
	{
		while (pt.j < board->j && j < piece->j)
		{
			if (piece->brd[i][j] == '*' && (board->brd[pt.i][pt.j] == game->player.me
				|| board->brd[pt.i][pt.j] == game->player.me + 32))
				touch++;	
			else if (piece->brd[i][j] == '*' && board->brd[pt.i][pt.j] != '.')
				return (0);
			pt.j++;
			j++;
		}
		while (j < piece->j)
		{
			if (piece->brd[i][j] != '.')
				return (0);
			j++;
		}
		j = 0;
		pt.j = start;
		pt.i++;
		i++;
	}
	while (i < piece->i)
	{
		while(j < piece->j)
		{
			if (piece->brd[i][j] != '.')
				return (0);
			j++;
		}
		i++;
		j = 0;
	}
	return (touch == 1 ? 1 : 0);
}
