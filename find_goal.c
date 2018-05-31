/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_goal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 17:39:22 by ydeineha          #+#    #+#             */
/*   Updated: 2018/05/26 17:39:27 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_coord	*find_goal(t_coord pt, t_brd *board, t_filler *game)
{
	static t_coord	*edge = NULL;
	t_coord			*goal_new;//free
	int				k;
	int				n;
	int				dst;

	k = 0;
	n = 0;
	goal_new = (t_coord *)malloc(sizeof(t_coord) * 3);
	if (!goal_new)
		return (NULL);
	goal_new[2].i = -1;
	if (!edge)
		edge = set_edge(board->i, board->j);
	while (k < 4)
	{
		dst = dst_mnh(edge[k], pt);
		game->map[edge[k].i][edge[k].j] = dst;
		k++;
	}
	goal_for_pt(game, goal_new, edge, pt);
	clean_map(game);
	// ft_printf("goal1 = (%i,%i)\n", goal_new[0].i, goal_new[0].j);
	// ft_printf("goal2 = (%i,%i)\n", goal_new[1].i, goal_new[1].j);
	return (goal_new);
}

void	goal_for_pt(t_filler *game, t_coord *goal, t_coord *edge, t_coord pt)
{
	static int	n = 0;
	static int	n_max = 1;
	int			k;
	int			min;
	int			flag;

	k = -1;
	min = -1;
	// ft_printf("I'm here 1!!!\n");
	// ft_printf("n = %i n_max = %i\n", n, n_max);
	while (++k < 4)
	{
		if (game->map[edge[k].i][edge[k].j] >= 0 && (min < 0 ||
			(min >= 0 && min > game->map[edge[k].i][edge[k].j])))
		{
			goal[n] = edge[k];
			min = game->map[edge[k].i][edge[k].j];
			n_max = !min ? n_max + 1 : n_max;
		}
	}
	game->map[goal[n].i][goal[n].j] = -1;
	// if (n < n_max)
	// {
	// 	n++;
	// 	goal_for_pt(game, goal, edge, pt);
	// }
	// else
	// 	set_goal(game, goal, edge, pt);
	// n_max = 1;
	// n = 0;
	flag = n < n_max ? 1 : 0;
	n = flag ? n + 1 : n;
	flag ? goal_for_pt(game, goal, edge, pt) : set_goal(game, goal, edge, pt);
	n_max = 1;
	n = 0;
}

void	set_goal(t_filler *game, t_coord *goal, t_coord *edge, t_coord pt)
{
	// ft_printf("I should be here\n");
	// ft_printf("goal[0] = (%i, %i)\ngoal[1] = (%i, %i)\n", goal[0].i, goal[0].j, goal[1].i, goal[1].j);
	// ft_printf("pt = (%i, %i)\n", pt.i, pt.j);
	if (goal[2].i >= 0)
	{
		//ft_printf("I'm here 2\n");
		if (goal[0].i == goal[1].i)
			goal[1].j = pt.j - ALT >= 0 ? pt.j - ALT : pt.j + ALT;
		else if (goal[0].j == goal[1].j)
			goal[1].i = pt.i - ALT >= 0 ? pt.i - ALT : pt.i + ALT;
		if (goal[0].i == goal[2].i)
			goal[0].j = pt.j - ALT >= 0 ? pt.j - ALT : pt.j + ALT;
		else if (goal[0].j == goal[2].j)
			goal[0].i = pt.i - ALT >= 0 ? pt.i - ALT : pt.i + ALT;
	}
	else if (goal[0].i == goal[1].i && pt.j - ALT >= 0 && pt.j + ALT < game->size.j)
	{
		//ft_printf("I'm here 3\n");
		goal[0].j = pt.j - ALT;
		goal[1].j = pt.j + ALT;
	}
	else if (goal[0].j == goal[1].j && pt.i - ALT >= 0 && pt.i + ALT < game->size.i)
	{
		//ft_printf("I'm here 4\n");
		goal[0].i = pt.i - ALT;
		goal[1].i = pt.i + ALT;
	}
	else
		goal_for_pt(game, goal, edge, pt);
}

t_coord	*set_edge(int i, int j)
{
	t_coord	*edge;

	edge = (t_coord *)malloc(sizeof(t_coord) * 4);
	if (!edge)
		return (NULL);
	edge[0].i = 0;
	edge[0].j = 0;
	edge[1].i = 0;
	edge[1].j = j - 1;
	edge[2].i = i - 1;
	edge[2].j = 0;
	edge[3].i = i - 1;
	edge[3].j = j - 1;
	return (edge);
}

int		dst_mnh(t_coord a, t_coord b)
{
	int i_sum;
	int	j_sum;

	i_sum = a.i >= b.i ? a.i - b.i : b.i - a.i;
	j_sum = a.j >= b.j ? a.j - b.j : b.j - a.j;
	return (i_sum + j_sum);
}

void	clean_map(t_filler *game)
{
	int	i;
	int j;

	i = -1;
	j = -1;
	while (++i < game->size.i)
	{
		while (++j < game->size.j)
			game->map[i][j] = -1;
		j = -1;
	}
}
