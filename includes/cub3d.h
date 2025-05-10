/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:40:37 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/10 16:07:41 by ulmagner         ###   ########.fr       */
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
	double			ms;
	// int			i;
	t_map	*h;
}	t_player;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*img_path;
	int		w;
	int		h;
}	t_image;

typedef struct s_window
{
	void	*mlx;
	void	*main;
	int		main_w;
	int		main_h;
	t_image	image;
}	t_window;

typedef struct s_raycasting
{
	double	x;
	double	y;
	double	tex_x;
	int		mapx;
	int		mapy;
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

typedef struct s_movement
{
	bool	move[65535];
	int		keycode;
	bool	i_move[4];
}	t_movement;

typedef struct s_fail
{
	int	a;
	int	b;
	int	k;
	int	j;
	int	i;
}	t_fail;

typedef struct s_texture
{
	int			*nbr_a;
	int			*nbr_i;
	int			nbr_image;
	char		**path_texture;
	t_image		***tiles;
	t_fail		fail;
}	t_texture;

typedef struct s_all
{
	t_window	window;
	t_info		info;
	t_player	player;
	t_map		*map;
	t_raycasting	ray;
	t_color		argb;
	t_image		image;
	t_movement	movement;
	t_texture	tex;
	int			i;
	int			step;
	int			ac;
	float		vision;
	char		**av;
	double		time;
	double		oldtime;
}	t_all;

void	rendering_image(t_image *image, t_all *all, int xscreen);
t_map	*get_node_at(t_map *head, int x, int y);
void	check_floor(char *line, t_texture *tex);
void	check_wall(char *line, t_texture *tex);
int		get_paths(char *file, t_texture *tex);
int		split_tile(t_texture *tex, t_all *all);
void	dir_up(t_player *player, t_movement *movement, t_all *all);
void	dir_down(t_player *player, t_movement *movement, t_all *all);
void	dir_left(t_player *player, t_movement *movement, t_all *all);
void	dir_right(t_player *player, t_movement *movement, t_all *all);
int		movement_handling(t_all *all);
int 	movement_p(int keycode, t_all *all);
int 	movement_r(int keycode, t_all *all);
void	ft_pixel_put(t_window *window, int x, int y, int color);
unsigned int	get_pixel_color(t_image *image, int x, int y);
int		launcher(t_all *all);
int		error_handling(int ac, char **av, t_info *info);
int		empty_string(t_info *info);
int		get_map(t_info *info, int *l, int *c);
void	ft_freetex(t_texture *tex);
void	ft_clearall(t_all *all);
void	ft_freeplayer(t_player *player);
void	ft_freeinfo(t_info *info);
void	ft_tabfree(char **tab);
void	ft_freemap(t_map **map);
int		check_close_map(t_map **map, t_info *info, t_all *all);
void	chain_map(t_map **curr, t_map **head, t_map *node);
void	chain_map_updown(t_map *node, t_info *info, t_map **head, t_map **curr);
int		make_list(int *i, t_map **node, t_all *all);
void	print_map(t_map **head, t_info *info);
int	    map_handling(t_info *info, t_map **map, t_all *all);
int	    main(int ac, char **av);
#endif //CUB3D
