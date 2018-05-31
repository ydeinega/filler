/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:30:41 by ydeineha          #+#    #+#             */
/*   Updated: 2018/05/22 14:30:44 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	put_piece(t_brd *board, t_brd *piece, int player)
{
	static t_filler	*game = NULL;
	t_coord			point;
	
	if (!game)
	{
		game = (t_filler *)malloc(sizeof(t_filler));
		create_game(game, board, player);	
	}
	set_fin_goals(game, board);
	point = find_point(game, board, piece);
	ft_printf("point = (%i, %i)\n", point.i, point.j);
	// ft_printf("goal1 = (%i, %i)\n", game->goal1.i, game->goal1.j);
	// ft_printf("goal2 = (%i, %i)\n", game->goal2.i, game->goal2.j);
	//piece free
}

void	create_game(t_filler *game, t_brd *board, int player)
{
	int	i;
	int j;

	i = -1;
	j = -1;
	game->map = (int **)malloc(sizeof(int *) * board->i);
	while (++i < board->i)
		game->map[i] = (int *)malloc(sizeof(int) * board->j);
	game->first = 1;
	game->player.me = player == 1 ? 'O' : 'X';
	game->player.enemy = player == 1 ? 'X' : 'O';
	game->size.i = board->i;
	game->size.j = board->j;
	clean_map(game);
}

void	set_fin_goals(t_filler *game, t_brd *board)
{
	t_coord		*goal_new;//free
	t_coord		pt;
	int			i;
	int			j;

	i = -1;
	j = -1;
	goal_new = NULL;
	while (++i < board->i)
	{
		while (++j < board->j)
		{
			if (board->brd[i][j] == game->player.enemy)
			{
				pt.i = i;
				pt.j = j;
				goal_new = find_goal(pt, board, game);
				if (game->first)//эту часть можно вынести в отдельную ф-ию
				{
					game->first = 0;
					game->player.enemy += 32;
					game->goal1 = goal_new[0];
					game->goal2 = goal_new[1];
				}
				else
				{
					write_max_dst(game, goal_new);
					compare_goals(game, goal_new);
					clean_map(game);	
				}
				free(goal_new);
			}
		}
		j = -1;
	}
}
// ft_printf("I'm here\n");
					// ft_printf("goal1 = (%i, %i)\n", game->goal1.i, game->goal1.j);
					// ft_printf("goal2 = (%i, %i)\n", game->goal2.i, game->goal2.j);
					// ft_printf("gnew1 = (%i, %i)\n", goal_new[0].i, goal_new[0].j);
					// ft_printf("gnew2 = (%i, %i)\n", goal_new[1].i, goal_new[1].j);
// ft_printf("RESULT\n");
					// ft_printf("goal1 = (%i, %i)\n", game->goal1.i, game->goal1.j);
					// ft_printf("goal2 = (%i, %i)\n", game->goal2.i, game->goal2.j);
//дальше если игра первая, то новые гоулы присваиваются в структуру гейм 
// и переменная ферст меняется на ноль и брейк
//если игра не первая, то мы отправляем новые гоулы и старые на сравнение
//в функцию, которая запишет новые гоулы в гейм

void	compare_goals(t_filler *game, t_coord *goal_new)
{
	static int	n = 1;
	int			i;
	int			j;
	int			max;

	i = 0;
	j = 0;
	max = -1;
	while (++i < game->size.i)
	{
		while (++j < game->size.j)
		{
			if (game->map[i][j] >= 0 && (max < 0 || (max >= 0 && max < game->map[i][j])))
			{
				game->goal1.i = n == 1 ? i : game->goal1.i;
				game->goal1.j = n == 1 ? j : game->goal1.j;
				game->goal2.i = n == 2 ? i : game->goal2.i;
				game->goal2.j = n == 2 ? j : game->goal2.j;
				max = game->map[i][j];
			}
		}
		j = -1;
	}
	game->map[game->goal1.i][game->goal1.j] = -1;
	if (++n == 2)
		compare_goals(game, goal_new);
	else
		n = 1;
}

void	write_max_dst(t_filler *game, t_coord *goal_new)
{
	t_coord array[4];
	int		i;
	int		n;
	int		max;
	int		new;

	i = -1;
	max = -1;
	n = -1;
	array[0] = goal_new[0];
	array[1] = goal_new[1];
	array[2] = game->goal1;
	array[3] = game->goal2;
	while (++i < 4)
	{
		while (++n < 4)
		{
			new = n != i ? dst_mnh(array[i], array[n]) : new;
			if (n != i && (max < 0 || (max >= 0 && max < new)))
			{
				max = new;
				game->map[array[i].i][array[i].j] = max;
			}
		}
		max = -1;
		n = -1;
	}
}

// print board
// //
	// int i, j;
	// i = 0;
	// j = 0;
	// while (i < board->i)
	// {
	// 	while (j < board->j)
	// 	{
	// 		ft_printf("%c", board->brd[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	j = 0;
	// 	i++;
	// }
	//

/* print map
	int i, j;
	i = 0;
	j = 0;
	while (i < game->size.i)
	{
		while (j < game->size.j)
		{
			ft_printf("%d ", game->map[i][j]);
			j++;
		}
		ft_printf("\n");
		j = 0;
		i++;
	}
	*/