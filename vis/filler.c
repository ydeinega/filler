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

t_brd	*create_brd(char *line)
{
	int		i;
	t_brd	*board;

	i = -1;
	board = (t_brd *)malloc(sizeof(t_brd));
	board->i = ft_atoi(ft_strchr(line, ' '));
	board->j = ft_atoi(ft_strrchr(line, ' '));
	board->brd = (char **)malloc(sizeof(char *) * (board->i + 1));
	if (!board->brd)
		return (NULL);
	board->brd[board->i] = NULL;
	while (++i < board->i)
		board->brd[i] = ft_strnew(board->j);
	return (board);
}

void	fill_board(char **board, char *line, int *type)
{
	static int i = 0;

	if (*type == BOARD)
		board[i] = ft_strcpy(board[i], &ft_strchr(line, ' ')[1]);
	else
		board[i] = ft_strcpy(board[i], line);
	*type = board[i + 1] ? *type : 0;
	i = board[i + 1] ? i + 1 : 0;
}

void	clean_board(t_brd **board)
{
	int i;

	i = 0;
	while (i < (*board)->i)
	{
		free((*board)->brd[i]);
		i++;
	}
	free((*board)->brd);
	free(*board);
	*board = NULL;
}

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
