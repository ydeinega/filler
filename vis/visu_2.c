#include "filler.h"
#include <fcntl.h>//
#include <ncurses.h>
#include <stdio.h>

void	create_window(t_visu *game)
{
	WINDOW	*win;
	WINDOW	*win1;
	WINDOW	*win2;
	WINDOW	*win3;
	//int starty, startx;
	int i;
	i = 2;
	//find_start(game, &starty, &startx);
	printw ("i = %i j = %i\n", game->board->i, game->board->j);
	refresh();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	game->win = newwin(2, 3, 10, 10);
	win1 = newwin(2, 3, 10, 7);
	win = newwin(2, 3, 10, 13);
	win2 = newwin(2, 3, 9, 13);
	win3 = newwin(2, 3, 9, 10);
	//game->win = newwin(game->board->i * 2 + 1, game->board->j * 2, 10, 10);
	box(game->win, 0, 0);
	box(win1, 0, 0);
	box(win, 0, 0);
	box(win2, 0, 0);
	box(win3, 0, 0);
	wbkgd(game->win, COLOR_PAIR(1) | A_BOLD);
	//wbkgdset(game->win, COLOR_PAIR(1));
	//mvwprintw(game->win, 1, 1, "ccc");
	// while (i < game->board->i * 2)
	// {
	// 	mvwhline(game->win, i, 1, ACS_HLINE, game->board->j * 2 - 2);
	// 	i += 2;
	// }
	// i = 2;
	// while (i < game->board->j * 2)
	// {
	// 	mvwvline(game->win, 1, i, ACS_VLINE, game->board->i * 2);
	// 	i += 2;
	// }
	wrefresh(game->win);
	wrefresh(win1);
	wrefresh(win);
	wrefresh(win2);
	wrefresh(win3);
}

void	print_first(t_visu *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < game->board->i)
	{
		while (j < game->board->j)
		{
			if (game->first)
				mvwprintw(game->win, i + 1, j + 1, "%c", game->board->brd[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	wrefresh(game->win);
	usleep(1000000);
}

void	initialize(t_visu *game)
{
	create_window(game);
	//print_first(game);
}

void	print_board(t_visu *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (game->first)
	{
		initialize(game);//this function prints names and window and fields
		game->first = 0;
	}
	// else
	// {	
	// 	while (i < game->board->i)
	// 	{
	// 		while (j < game->board->j)
	// 		{
			
	// 			if (game->board->brd[i][j] == 'o' || game->board->brd[i][j] == 'x')
	// 			{
	// 				mvwprintw(game->win, i + 1, j + 1, "%c", game->board->brd[i][j]);
	// 				usleep(15000);
	// 				wrefresh(game->win);
	// 			}
	// 			j++;
	// 		}
	// 		j = 0;
	// 		i++;
	// 	}
	// }
	game->type = -1;
}

void	get_name(char *line, t_visu *game)
{
	if (ft_atoi(&(ft_strchr(line, 'p')[1])) == 1)
		game->name_p1 = ft_strsub(line, ft_strchr(line, '/') - line + 1, ft_strchr(line, '.') - ft_strchr(line, '/') - 1);
	if (ft_atoi(&(ft_strchr(line, 'p')[1])) == 2)
	{
		game->name_p2 = ft_strsub(line, ft_strchr(line, '/') - line + 1, ft_strchr(line, '.') - ft_strchr(line, '/') - 1);
		printw("\nFILLER\n");
		printw("\np1 = |%s|   ", game->name_p1);
		printw("p2 = |%s|\n", game->name_p2);
		refresh();
	}
}

void	get_score(char *line, t_visu *game)
{
	game->type = FIN;

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
	game->win = NULL;
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
			refresh();
		}
	}
	usleep(5000000);
	endwin();
	//clean_game_visu(game);
}
