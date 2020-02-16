/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:23:16 by kcharla           #+#    #+#             */
/*   Updated: 2020/02/17 00:45:33 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include "SDL.h"

# define COLOR_MAX 255
# define COLOR_MIN 0
# define ALPHA_MAX 255
# define ALPHA_MIN 0

typedef enum		e_result_code
{
	OK,
	EXIT,
	RENDER
}					t_result_code;

typedef struct		s_color
{
	t_byte			r;
	t_byte			g;
	t_byte			b;
	t_byte			a;
}					t_color;

typedef struct		s_texture
{
	size_t			size_x;
	size_t			size_y;
	t_byte			*img;
}					t_texture;

typedef struct		s_window
{
	t_texture		texture;
	SDL_Window		*sdl_window;
	SDL_Texture		*sdl_texture;
	SDL_Renderer	*sdl_renderer;
}					t_window;

typedef struct		s_rtv1
{
	t_window		*window;
	int				velocity_up_down;
	int				velocity_left_right;
	int				velocity_forward_backward;
	t_bool			LMB_down;
}					t_rtv1;

/*
** events.c
*/

int					on_key_down(t_rtv1 *rtv1, SDL_Scancode scancode);
int					on_key_up(t_rtv1 *rtv1, SDL_Scancode scancode);
int					on_mouse_down(t_rtv1 *rtv1, SDL_Scancode scancode);
int					on_mouse_move(t_rtv1 *rtv1, int x, int y);
int					on_mouse_up(t_rtv1 *rtv1, SDL_Scancode scancode);

/*
** window.c
*/

int					window_init(t_window **win, size_t w, size_t h);
int					window_render(t_window *win);

/*
** destroy.c
*/

void				destroy_window(t_window *win);
void				destroy_rtv1(t_rtv1 *rtv1);

/*
** loop.c
*/

int					rtv1_loop(t_rtv1 *rtv1);
int					window_render(t_window *win);

/*
** texture.c
*/

int					texture_init(t_texture *texture, size_t w, size_t h);
void				texture_fill(t_texture texture, t_color col);
void				texture_put_pixel(t_texture texture, t_color col,
						size_t x, size_t y);

/*
** color.c
*/

t_color				color_alpha(t_byte r, t_byte g, t_byte b, t_byte a);
t_color				color(t_byte red, t_byte green, t_byte blue);

#endif
