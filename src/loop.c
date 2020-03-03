/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 18:13:19 by kcharla           #+#    #+#             */
/*   Updated: 2020/03/03 21:51:31 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		check_input(t_rtv1 *rtv1)
{
	rtv1->vel_forward = 0;
	rtv1->vel_right = 0;
	rtv1->vel_up = 0;

	if (rtv1->w && !rtv1->s)
		rtv1->vel_forward = VEL_DELTA;
	if (rtv1->s && !rtv1->w)
		rtv1->vel_forward = -VEL_DELTA;

	if (rtv1->d && !rtv1->a)
		rtv1->vel_right = VEL_DELTA;
	if (rtv1->a && !rtv1->d)
		rtv1->vel_right = -VEL_DELTA;

	if (rtv1->q && !rtv1->e)
		rtv1->vel_up = VEL_DELTA;
	if (rtv1->e && !rtv1->q)
		rtv1->vel_up = -VEL_DELTA;

	if (rtv1->vel_up != 0 || rtv1->vel_right != 0 || rtv1->vel_forward != 0)
	{
		return (MOVE);
	}
	return (OK);
}
int		check_event(t_rtv1 *rtv1, SDL_Event event)
{
	int					result_code;

	result_code = UNSET;
	if (event.type == SDL_KEYDOWN)
		result_code = on_key_down(rtv1, event.button.button);
	else if (event.type == SDL_KEYUP)
		result_code = on_key_up(rtv1, event.button.button);
	else if (event.type == SDL_MOUSEBUTTONDOWN)
		result_code = on_mouse_down(rtv1, event.button.button);
	else if (event.type == SDL_MOUSEBUTTONUP)
		result_code = on_mouse_up(rtv1, event.button.button);
	else if (event.type == SDL_MOUSEMOTION)
		result_code = on_mouse_move(rtv1, event.motion.x, event.motion.y);
	if (event.type == SDL_QUIT)
		result_code = EXIT;
	return (result_code);
}

int		iterate_events(t_rtv1 *rtv1)
{
	SDL_Event			event;
	t_bool				render_needed;
	int					result_code;

	if (rtv1 == NULL)
		return (ERROR);
	render_needed = FALSE;
	while (SDL_PollEvent(&event))
	{
		result_code = check_event(rtv1, event);
		if (result_code == EXIT)
			return (EXIT);
		render_needed = (result_code == RENDER) ? TRUE : render_needed;
	}
	return (check_input(rtv1));
}

int		redraw(t_rtv1 *rtv1)
{
	if (rtv1 == NULL)
		return (ft_puterror(1, "redraw(): pointer rtv1 is NULL"));
	if (rtv1->window == NULL)
		return (ft_puterror(2, "redraw(): pointer rtv1->window is NULL"));
	texture_fill(rtv1->window->texture, color(0, 0, 0));
	if (project(rtv1) < 0)
		return (ft_puterror(3, "rtv1_loop(): project()"));
	if (window_render(rtv1->window) < 0)
		return (ft_puterror(4, "rtv1_loop(): window_render()"));
	return (0);
}

int		rtv1_loop(t_rtv1 *rtv1)
{
	int				result_code;

	if (rtv1 == NULL)
		return (ft_puterror(1, "rtv1_loop(): pointer rtv1 is NULL"));
	if (redraw(rtv1) < 0)
		return (ft_puterror(3, "rtv1_loop(): problem running redraw()"));
	while (TRUE)
	{
		if ((result_code = iterate_events(rtv1)) < 0)
			return (ft_puterror(4, "rtv1_loop(): iterate_events()"));
		else if (result_code == EXIT)
			break ;
		if (result_code == MOVE)
		{
			camera_move_local(&rtv1->camera, (t_vec) {rtv1->vel_forward, rtv1->vel_right, rtv1->vel_up});
			result_code = RENDER;
		}
		if (result_code == RENDER)
		{
			ft_putendl("calling redraw...");
			if (redraw(rtv1) < 0)
				return (ft_puterror(3, "rtv1_loop(): redraw()"));
		}
	}
	return (EXIT);
}
