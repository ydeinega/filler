/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:31:28 by ydeineha          #+#    #+#             */
/*   Updated: 2018/05/22 14:31:32 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define BOARD 1
# define PIECE -1
# define ALT 1
# include "./libft/libft.h"

typedef struct	s_coord
{
	int			i;
	int			j;
}				t_coord;

typedef struct	s_brd
{
	int			i;
	int			j;
	//t_coord	size;
	char		**brd;
	char		**tmp;
}				t_brd;

typedef struct	s_chr
{
	char		me;
	char		enemy;
}				t_chr;

typedef struct	s_filler
{
	int			**map;
	t_coord		size;
	int			first;
	int			count;
	t_coord		goal1;
	t_coord		goal2;
	t_chr		player;
}				t_filler;

t_brd			*create_board(char *line);
void			fill_board(char **board, char *line, int *type);
void			put_piece(t_brd *board, t_brd **piece, int player);
void			create_game(t_filler *game, t_brd *board, int player);
void			set_fin_goals(t_filler *game, t_brd *board, int player);
t_coord			*find_goal(t_coord pt, t_brd *board, t_filler *game);
int				dst_mnh(t_coord a, t_coord b);
t_coord			*set_edge(int i, int j);
void			goal_for_pt(t_filler *game, t_coord *goal, t_coord *edge, t_coord pt);
void			set_goal(t_filler *game, t_coord *goal, t_coord *edge, t_coord pt);
void			compare_goals(t_filler *game, t_coord *goal_new);
void			clean_map(t_filler *game);
void			write_max_dst(t_filler *game, t_coord *goal_new);
t_coord			find_point(t_filler *game, t_brd *board, t_brd *piece);
int				check_piece(t_filler *game, t_brd *board, t_brd *piece, t_coord pt);
void			clean_board(t_brd **board);
void			set_point(t_filler *game, t_coord tmp, t_coord *point, int *min);
void			set_count(t_filler *game, t_brd *board, t_brd *piece, t_coord pt);
int				check_count(t_filler *game, t_coord point);
void			change_board(t_filler *game, t_brd *board);
char			**copy_board(t_brd *board, char **brd);
#endif