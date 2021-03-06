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
	char		**brd;
}				t_brd;

typedef struct	s_chr
{
	char		me;
	char		enemy;
}				t_chr;

typedef struct	s_filler
{
	t_coord		point;
	t_coord		tmp;
	t_coord		touch;
	t_chr		player;
	int			min;
}				t_filler;

t_brd			*create_brd(char *line);
void			fill_board(char **board, char *line, int *type);
void			put_piece(t_brd *board, t_brd **piece, int player);
t_filler		*create_game(int player);
void			check_min(t_filler *game, t_brd *board);
int				dst_mnh(t_coord a, t_coord b);
int				check_piece(t_filler *game, t_brd *board,
				t_brd *piece, t_coord pt);
void			clean_board(t_brd **board);
#endif
