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
