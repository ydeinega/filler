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

void	create_window(t_visu *game, int max_i, int max_j)
{
	int i;
	int j;

	i = max_i - game->board->i - 2;
	j = (max_j - game->board->j - 2) / 2;
	if (i < 4)
		i = 0;
	else if (i == 4)
		i = 3;
	else if (i < 10)
		i = 4;
	else
		i = 6;
	game->wpos.i = i;
	game->wpos.j = j;
	game->score1.i = i < 4 ? 0 : i + game->board->i + 2;
	game->score2.i = i < 4 ? 0 : i + game->board->i + 2;
	game->score_pos = i + game->board->i + 2;
	game->win = newwin(game->board->i + 2, game->board->j + 2, i, j);
	box(game->win, 0, 0);
	refresh();
}

void	print_first(t_visu *game, int max_i, int max_j)
{
	int i;
	int j;
	int name1_pos;
	int name2_pos;

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
	mvprintw(2, (max_j - ft_strlen("F I L L E R")) / 2, "F I L L E R");
	attron(COLOR_PAIR(1));
	name1_pos = (max_j - ft_strlen(game->name_p1) - ft_strlen(game->name_p2) - 10) / 2;
	name2_pos = name1_pos + ft_strlen(game->name_p1) + 10;
	game->score1_pos = name1_pos;
	game->score2_pos = name2_pos;
	mvprintw(4, name1_pos, "%s", game->name_p1);
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	mvprintw(4, name2_pos, "%s", game->name_p2);
	attroff(COLOR_PAIR(2));
	refresh();
}

void	initialize(t_visu *game)
{
	int max_i;
	int max_j;

	getmaxyx(stdscr, max_i, max_j);
	if (max_i < game->board->i || max_j < game->board->j)
	{
		attron(A_BOLD);
		printw("\nPlease, make the window bigger and start the game once again!\n");
		refresh();
		usleep(5000000);
		clean_game_visu(game);
		endwin();
		exit(1);
	}
	game->max_i = max_i;
	game->max_j = max_j;
	create_window(game, max_i, max_j);
	print_first(game, max_i, max_j);
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
	int pos;

	pos = 0;
	if (ft_strchr(line, 'O'))
		game->score_p1 = ft_atoi(&(ft_strchr(line, ':')[1]));
	if (ft_strchr(line, 'X'))
	{
		game->score_p2 = ft_atoi(&(ft_strchr(line, ':')[1]));
		attron(COLOR_PAIR(1));
		mvprintw(game->score_pos, game->score1_pos, "%d", game->score_p1);
		if (game->score_p1 > game->score_p2)
		{
			pos = (game->max_j - ft_strlen(game->name_p1) - 10) / 2; 
			mvprintw(game->score_pos + 2, pos, "%s W I N S !", game->name_p1);
		}
		attroff(COLOR_PAIR(1));
		attron(COLOR_PAIR(2));
		mvprintw(game->score_pos, game->score2_pos, "%d", game->score_p2);
		if (game->score_p1 < game->score_p2)
		{
			pos = (game->max_j - ft_strlen(game->name_p2) - 10) / 2; 
			mvprintw(game->score_pos + 2, pos, "%s W I N S !", game->name_p2);
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
