/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 18:58:43 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/24 18:58:48 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	initscr();
	raw();
	noecho();
	curs_set(0);
	game = create_game_visu();
	while (get_next_line(0, &line) > 0)
	{
		game->type == BOARD ?
		fill_board(game->board->brd, line, &(game->type)) : -1;
		game->type = game->type > BOARD ? game->type - 1 : game->type;
		game->type = ft_strstr(line, "Plateau") ? BOARD + 1 : game->type;
		game->board = !(game->board) && ft_strstr(line, "Plateau") ?
		create_brd(line) : game->board;
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
