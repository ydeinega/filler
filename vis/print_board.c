/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_board.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 21:02:58 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/24 21:03:02 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
				print_move(game, i, j);
			}
			j = -1;
		}
	}
	game->type = -1;
}

void	print_move(t_visu *game, int i, int j)
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

void	get_name(char *line, t_visu *game)
{
	if (ft_atoi(&(ft_strchr(line, 'p')[1])) == 1)
		game->name_p1 = ft_strsub(line, ft_strchr(line, '/') - line + 1,
			ft_strchr(line, '.') - ft_strchr(line, '/') - 1);
	if (ft_atoi(&(ft_strchr(line, 'p')[1])) == 2)
	{
		game->name_p2 = ft_strsub(line, ft_strchr(line, '/') - line + 1,
			ft_strchr(line, '.') - ft_strchr(line, '/') - 1);
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
		print_score(game);
	}
}

void	print_score(t_visu *game)
{
	attron(COLOR_PAIR(1));
	mvprintw(game->score1.i, game->score1.j,
		"%s = %d", game->name_p1, game->score_p1);
	if (game->score_p1 > game->score_p2)
	{
		game->wins.j = (game->max.j - ft_strlen(game->name_p1) - 10) / 2;
		mvprintw(game->wins.i, game->wins.j, "%s W I N S !", game->name_p1);
	}
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	mvprintw(game->score2.i, game->score2.j,
		"%s = %d", game->name_p2, game->score_p2);
	if (game->score_p1 < game->score_p2)
	{
		game->wins.j = (game->max.j - ft_strlen(game->name_p2) - 10) / 2;
		mvprintw(game->wins.i, game->wins.j, "%s W I N S !", game->name_p2);
	}
	attroff(COLOR_PAIR(2));
	refresh();
}
