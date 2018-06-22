#include "filler.h"
#include <fcntl.h>//
#include <ncurses.h>

void	print_board(t_visu *game)
{
	int i;
	int j;
	int time;

	i = 0;
	j = 0;
	time = 0;
	while (i < game->board->i)
	{
		while (j < game->board->j)
		{
			if (game->first)
				printw("%c", game->board->brd[i][j]);
			else if (game->board->brd[i][j] == 'o' || game->board->brd[i][j] == 'x')
			{
				mvprintw(i, j, "%c", game->board->brd[i][j]);
				while (time < 10000000)
					time++;
				time = 0;
				refresh();
			}
			j++;
		}
		if (game->first)
			printw("\n");
		j = 0;
		i++;
	}
	refresh();
	game->type = -1;
	if (game->first)
	{
		game->first = 0;
		attron(A_BLINK);
	}
}

void	get_name(char *line, t_visu *game)
{
	if (ft_atoi(&(ft_strchr(line, 'p')[1])) == 1)
		game->name_p1 = ft_strsub(line, ft_strchr(line, '/') - line + 1, ft_strchr(line, '.') - ft_strchr(line, '/') - 1);
	printw("name = |%s|\n", game->name_p1);
	refresh();
}

void	get_score(char *line, t_visu *game)
{
	game->type = FIN;

	printw("I'm here 1\n");
	refresh();
	int i;
	i = 0;
	while (i < 100000000)
		i++;
	i = 0;
	while (i < 100000000)
		i++;
	while (i < 100000000)
		i++;
}

t_visu	*create_game_visu(void)
{
	t_visu	*game;

	game = (t_visu *)malloc(sizeof(t_visu));
	if (!game)
		return (NULL);
	game->name_p1 = NULL;
	game->name_p2 = NULL;
	game->score_p1 = 0;
	game->score_p2 = 0;
	game->first = 1;
	game->board = NULL;
	game->prev = NULL;
	game->type = -1;
	return (game);
}

int		main(void)
{
	char	*line;
	t_visu	*game;
	int		ch;

	initscr();
	raw();
	noecho();
	curs_set(0);
	game = create_game_visu();
	while (get_next_line(0, &line) > 0)
	{
		game->type == BOARD ? fill_board(game->board->brd, line, &(game->type)) : -1;
		game->type = game->type > BOARD ? game->type - 1 : game->type;
		game->type = ft_strstr(line, "Plateau") ? BOARD + 1 : game->type;
		game->board = !(game->board) && ft_strstr(line, "Plateau") ? create_brd(line) : game->board;
		ft_strstr(line, "exec") ? get_name(line, game) : 0;
		ft_strstr(line, "fin") ? get_score(line, game) : 0;
		if (game->type == 0 && game->board)
			print_board(game);
		ft_strdel(&line);
		if (game->type == FIN)
		{
			//print_score(game);
			printw("I'm here 2\n");
			refresh();
			break ;	
		}
		// if (end_game(line))
		// 	break ;
		// endwin();
	}
	if (getch() == EOF)
	{
		printw("I'm here 3\n");
		refresh();
	}
	//endwin();
	//clean_game_visu(game);
}
