/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:40:37 by ulmagner          #+#    #+#             */
/*   Updated: 2025/03/31 12:03:01 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# define TILE_SIZE 64

typedef struct s_map
{
	char			i;
	int				x;
	int				y;
	int				x_pxl;
	int				y_pxl;
	int				is_visited;
	struct s_map	*right;
	struct s_map	*left;
	struct s_map	*up;
	struct s_map	*down;
	struct s_map	*player;
}	t_map;

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_info
{
	int		i_x;
	int		i_y;
	int		size_map;
	int		column;
	int		line;
	int		fd;
	char	*map;
}	t_info;

typedef struct s_player
{
	double		x;
	double		y;
	double		dx;
	double		dy;
	double		planex;
	double		planey;
	int			mapx;
	int			mapy;
	t_map	*h;
}	t_player;

typedef struct s_window
{
	void	*mlx;
	void	*main;
	int		main_w;
	int		main_h;
}	t_window;

typedef struct s_raycasting
{
	double	x_pxl;
	double	y_pxl;
	int		x;
	int		y;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
}	t_raycasting;

typedef struct s_all
{
	t_window	window;
	t_info		info;
	t_player	player;
	t_map		*map;
	t_raycasting	ray;
	t_color		argb;
	int			i;
	int			step;
	int			ac;
	float		vision;
	char		**av;
	double		time;
	double		oldtime;
}	t_all;

int		launcher(t_all *all);
int		error_handling(int ac, char **av, t_info *info);
int		empty_string(t_info *info);
int		get_map(t_info *info, int *l, int *c);
void	ft_clearall(t_all *all);
void	ft_freeplayer(t_player *player);
void	ft_freeinfo(t_info *info);
void	ft_tabfree(char **tab);
void	ft_freemap(t_map **map);
int		check_close_map(t_map **map, t_info *info, t_all *all);
void	chain_map(t_map **curr, t_map **head, t_map *node);
void	chain_map_updown(t_map *node, t_info *info, t_map **head, t_map **curr);
int		make_list(int *i, t_map **node, t_map **h, t_all *all);
void	print_map(t_map **head, t_info *info);
int	    map_handling(t_info *info, t_map **map, t_player *player, t_all *all);
int	    main(int ac, char **av);
#endif //CUB3D
