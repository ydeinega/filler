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
#include <fcntl.h>//del

t_brd	*create_board(char *line)
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

int		main(void)
{
	char	*line;
	t_brd	*board;
	t_brd	*piece;
	int		type;
	int		player;
	int		fd;//del

	board = NULL;
	piece = NULL;
	type = 0;
	fd = open("shit.txt", O_CREAT | O_WRONLY | O_APPEND);
	while (get_next_line(0, &line))//дозаписывать в файл
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		if (type == BOARD)
			fill_board(board->brd, line, &type);
		if (type == PIECE)
			fill_board(piece->brd, line, &type);
		type = type > BOARD ? type - 1 : type;
		type = ft_strstr(line, "Piece") ? PIECE : type;
		type = ft_strstr(line, "Plateau") ? BOARD + 1 : type;
		board = !board && ft_strstr(line, "Plateau") ? create_board(line) : board;
		piece = !piece && ft_strstr(line, "Piece") ? create_board(line) : piece;
		player = ft_strstr(line, "ydeineha") && ft_strstr(line, "exec") ?
		ft_atoi(&ft_strchr(line, 'p')[1]) : player;
		!type && board && piece ? put_piece(board, &piece, player) : 0;
		ft_strdel(&line);
	}
}

/*DELETE!
		int i;
		//ft_printf("\nplayer = %d\n", p);
		if (type == 0 && board)
		{
			i = 0;
			while (board->brd[i])
			{
				if (i == 0)
					ft_printf("\n");
				ft_printf("    %s\n", board->brd[i]);
				i++;
			}
		}
		
		if (type == 0 && piece)
		{
			i = 0;
			while (piece->brd[i])
			{
				if (i == 0)
					ft_printf("\n");
				ft_printf("%s\n", piece->brd[i]);
				i++;
			}
		}
		//TILL HERE*/



/*
exec p2 ydeineha
Piece 5 3:
.*.
.*.
.*.
.*.
...

Plateau 14 30:
012345678901234567890123456789
000 ..............................
001 ..............................
002 ..............................
003 .....X.......................X
004 ..............................
005 ..............................
006 ..............................
007 ..............................
008 ..............................
009 ..............................
010 ......................O.......
011 ..............................
012 ..............................
013 .............................X

Plateau 14 30:
012345678901234567890123456789
000 ..............................
001 ..............................
002 ..............................
003 .....X........................
004 ..............................
005 ..............................
006 ..............................
007 ..............................
008 ..............................
009 ......................o.......
010 ......................O.......
011 ..............................
012 ..............................
013 ..............................

Plateau 14 30:
012345678901234567890123456789
000 ..............................
001 ..............................
002 ..............................
003 .....X........................
004 ..............................
005 ..............................
006 ..............................
007 ..............................
008 ..............................
009 ......................O.......
010 ......................O.......
011 ..............................
012 ..............................
013 .........................o....

exec p2 ydeineha
Piece 4 3:
123
123
123
123

Plateau 14 30:
012345678901234567890123456789
000 ..............................
001 ..............................
002 ..............................
003 .....X........................
004 ..............................
005 ..............................
006 ..............................
007 ..............................
008 ..............................
009 ..............................
010 ..............................
011 ..............................
012 ..............................
013 .......................ooo....
*/
