/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 21:04:53 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/24 21:04:56 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	initialize(t_visu *game)
{
	getmaxyx(stdscr, game->max.i, game->max.j);
	get_positions(game);
	print_first(game);
	if (game->wpos.i == 0)
	{
		usleep(1000000);
		werase(stdscr);
		refresh();
	}
	game->win = newwin(game->board->i + 2, game->board->j + 2,
		game->wpos.i, game->wpos.j);
	box(game->win, 0, 0);
	refresh();
	game->first = 0;
	usleep(500000);
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
	mvprintw(game->filler.i, game->filler.j, "F I L L E R");
	attron(COLOR_PAIR(1));
	mvprintw(game->name1.i, game->name1.j, "%s", game->name_p1);
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	mvprintw(game->name2.i, game->name2.j, "%s", game->name_p2);
	attroff(COLOR_PAIR(2));
	refresh();
}
