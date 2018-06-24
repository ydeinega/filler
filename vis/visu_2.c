#include "filler.h"

void	clean_game_visu(t_visu *game)
{
	if (game->name_p1)
		ft_strdel(&(game->name_p1));
	if (game->name_p2)
		ft_strdel(&(game->name_p2));
	if (game->win)
		delwin(game->win);
	if (game->board)
		clean_board(&(game->board));
}

void	get_jpositions(t_visu *game)
{
	game->filler.j = (game->max.j - ft_strlen("F I L L E R")) / 2;
	game->name1.j = game->filler.j - ft_strlen(game->name_p1) - 5;
	game->name2.j = game->filler.j + ft_strlen("F I L L E R") + 5;
	game->score1.j = game->name1.j;
	game->score2.j = game->name2.j;
}

void	get_ipositions(t_visu *game)
{
	if (game->wpos.i == 0)
	{
		game->filler.i = 2;
		game->name1.i = 4;
		game->score1.i = 6;
		game->wins.i = 8;
	}
	if (game->wpos.i == 2 || game->wpos.i == 3)
	{
		game->filler.i = 0;
		game->name1.i = 1;
		game->score1.i = game->wpos.i + game->board->i + 2;
		game->wins.i = game->score1.i + 1;
	}
	if (game->wpos.i == 6)
	{
		game->filler.i = 2;
		game->name1.i = 4;
		game->score1.i = game->wpos.i + game->board->i + 2;
		game->wins.i = game->score1.i + 2;
	}
	game->score2.i = game->score1.i;
	game->name2.i = game->name1.i;
}

void	get_positions(t_visu *game)
{
	int i;
	int j;

	i = game->max.i - game->board->i - 2;
	j = (game->max.j - game->board->j - 2) / 2;
	if (i < 4)
		i = 0;
	else if (i == 4)
		i = 2;
	else if (i < 10)
		i = 3;
	else
	{
		i = 6;
		game->filler.i = 2;
		game->name1.i = 4;
		game->name2.i = 4;
	}
	game->wpos.i = i;
	game->wpos.j = j;
	get_ipositions(game);
	get_jpositions(game);
}

void	print_first(t_visu *game)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < game->board->i)
	{
		while (++j < game->board->j)
			mvwprintw(game->win, i + 1, j + 1, "%c", game->board->brd[i][j]);
		j = -1;
	}
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(2, COLOR_WHITE, COLOR_CYAN);
	attron(A_BLINK | A_BOLD);
	mvprintw(game->filler.i, game->filler.j , "F I L L E R");
	attron(COLOR_PAIR(1));
	mvprintw(game->name1.i, game->name1.j, "%s", game->name_p1);
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	mvprintw(game->name2.i, game->name2.j, "%s", game->name_p2);
	attroff(COLOR_PAIR(2));
	refresh();
}

void	initialize(t_visu *game)
{
	getmaxyx(stdscr, game->max.i, game->max.j);
	// if (game->max.i < game->board->i || game->max.j < game->board->j)
	// {
	// 	attron(A_BOLD);
	// 	printw("\nPlease, make the window bigger and start the game once again!\n");
	// 	refresh();
	// 	usleep(5000000);
	// 	clean_game_visu(game);
	// 	endwin();
	// 	exit(1);
	// }
	get_positions(game);
	print_first(game);
	if (game->wpos.i == 0)
	{
		usleep(1000000);
		werase(stdscr);
		refresh();
	}
	game->win = newwin(game->board->i + 2, game->board->j + 2, game->wpos.i, game->wpos.j);
	box(game->win, 0, 0);
	refresh();
	game->first = 0;
	usleep(500000);
}

void	print_board(t_visu *game)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (game->first)
		initialize(game);
	else
	{	
		while (++i < game->board->i)
		{
			while (++j < game->board->j)
			{
			
				if (game->board->brd[i][j] == 'o')
				{
					wattron(game->win, COLOR_PAIR(1) | A_BLINK | A_BOLD);
					mvwprintw(game->win, i + 1, j + 1, "O");
					usleep(15000);
					wrefresh(game->win);
					wattroff(game->win, COLOR_PAIR(1) | A_BLINK | A_BOLD);
				}
				else if (game->board->brd[i][j] == 'x')
				{
					wattron(game->win, COLOR_PAIR(2) | A_BLINK | A_BOLD);
					mvwprintw(game->win, i + 1, j + 1, "X");
					usleep(15000);
					wrefresh(game->win);
					wattroff(game->win, COLOR_PAIR(2) | A_BLINK | A_BOLD);
				}
			}
			j = -1;
		}
	}
	game->type = -1;
}

void	get_name(char *line, t_visu *game)
{
	if (ft_atoi(&(ft_strchr(line, 'p')[1])) == 1)
		game->name_p1 = ft_strsub(line, ft_strchr(line, '/') - line + 1, ft_strchr(line, '.') - ft_strchr(line, '/') - 1);
	if (ft_atoi(&(ft_strchr(line, 'p')[1])) == 2)
	{
		game->name_p2 = ft_strsub(line, ft_strchr(line, '/') - line + 1, ft_strchr(line, '.') - ft_strchr(line, '/') - 1);
	}
}

void	get_score(char *line, t_visu *game)
{
	if (ft_strchr(line, 'O'))
		game->score_p1 = ft_atoi(&(ft_strchr(line, ':')[1]));
	if (ft_strchr(line, 'X'))
	{
		if (game->wpos.i == 0)
		{
			usleep(1000000);
			werase(stdscr);
			print_first(game);
			refresh();
		}
		game->score_p2 = ft_atoi(&(ft_strchr(line, ':')[1]));
		attron(COLOR_PAIR(1));
		mvprintw(game->score1.i, game->score1.j, "%s = %d", game->name_p1, game->score_p1);
		if (game->score_p1 > game->score_p2)
		{
			game->wins.j = (game->max.j - ft_strlen(game->name_p1) - 10) / 2; 
			mvprintw(game->wins.i, game->wins.j, "%s W I N S !", game->name_p1);
		}
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		mvprintw(game->score2.i, game->score2.j, "%s = %d", game->name_p2, game->score_p2);
		if (game->score_p1 < game->score_p2)
		{
			game->wins.j = (game->max.j - ft_strlen(game->name_p2) - 10) / 2; 
			mvprintw(game->wins.i, game->wins.j, "%s W I N S !", game->name_p2);
		}
		attroff(COLOR_PAIR(2));
		refresh();
	}
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
	}
	usleep(5000000);
	endwin();
	clean_game_visu(game);
}
