/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 00:29:47 by kcharla           #+#    #+#             */
/*   Updated: 2020/06/17 23:53:48 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_window		*window_init(size_t w, size_t h, const char *name)
{
	t_window		*win;

	if ((win = (t_window*)ft_malloc(sizeof(t_window))) == NULL)
		return (ft_puterr_null(1, "window_init(): cannot malloc window"));
	if ((win->sdl_window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN)) == NULL)
		return (ft_puterr_null(2, "window_init(): cannot create SDL window"));
	if ((win->sdl_renderer = SDL_CreateRenderer(
			win->sdl_window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
		return (ft_puterr_null(3, "window_init(): cannot create SDL renderer"));
	if ((win->sdl_texture = SDL_CreateTexture(win->sdl_renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h)) == NULL)
		return (ft_puterr_null(4, "window_init(): cannot create SDL texture"));
	if (SDL_SetTextureBlendMode(win->sdl_texture, SDL_BLENDMODE_BLEND) < 0)
	{
		return (ft_puterr_null(5,
				"window_init(): cannot set SDL texture blend mode"));
	}
	return (win);
}

int				win_update_from_camera(t_window *win, t_camera *cam)
{
	if (win == NULL || cam == NULL)
		return (ft_puterror(1, "Entered NULL pointer"));
	if (window_update_texture(win, cam->texture) < 0)
		return (ft_puterror(2, "Cannot update texture"));
	return (0);
}

int				window_update_texture(t_window *win, t_texture *texture)
{
	if (win == NULL || texture == NULL)
		return (ft_puterror(1, "Entered NULL pointer"));
	if (SDL_RenderClear(win->sdl_renderer) < 0)
	{
		return (ft_puterror(2,
				"window_render(): problem running SDL_RenderClear()"));
	}
	if (SDL_UpdateTexture(win->sdl_texture, NULL,
			texture->img, (int)texture->size_x * BYTES_PER_PIXEL) < 0)
	{
		return (ft_puterror(3,
				"window_render(): problem running SDL_UpdateTexture()"));
	}
	if (SDL_RenderCopy(win->sdl_renderer, win->sdl_texture, NULL, NULL) < 0)
	{
		return (ft_puterror(4,
				"window_render(): problem running SDL_RenderCopy()"));
	}
	SDL_RenderPresent(win->sdl_renderer);
	return (0);
}

void			window_free(t_window *win)
{
	if (win == NULL)
		return ;
	SDL_DestroyWindow(win->sdl_window);
	SDL_DestroyTexture(win->sdl_texture);
	SDL_DestroyRenderer(win->sdl_renderer);
	ft_free(win);
}
