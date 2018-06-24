/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:20:53 by ydeineha          #+#    #+#             */
/*   Updated: 2018/05/23 12:20:59 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(void)
{
	char	*line;
	t_brd	*board;
	t_brd	*piece;
	int		type;
	int		player;

	board = NULL;
	piece = NULL;
	type = 0;
	while (get_next_line(0, &line) > 0)
	{
		type == BOARD ? fill_board(board->brd, line, &type) : 0;
		type == PIECE ? fill_board(piece->brd, line, &type) : 0;
		type = type > BOARD ? type - 1 : type;
		type = ft_strstr(line, "Piece") ? PIECE : type;
		type = ft_strstr(line, "Plateau") ? BOARD + 1 : type;
		board = !board && ft_strstr(line, "Plateau") ? create_brd(line) : board;
		piece = !piece && ft_strstr(line, "Piece") ? create_brd(line) : piece;
		player = ft_strstr(line, "ydeineha") && ft_strstr(line, "exec") ?
		ft_atoi(&ft_strchr(line, 'p')[1]) : player;
		!type && board && piece ? put_piece(board, &piece, player) : 0;
		ft_strdel(&line);
	}
	clean_board(&board);
}
