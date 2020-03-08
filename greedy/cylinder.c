/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:49:44 by kcharla           #+#    #+#             */
/*   Updated: 2020/03/06 03:10:00 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	get_t(t_base_fig_cyl *cyl, t_vec ao_x_ab,
t_vec v_x_ab, double *ab2)
{
	t_double3	ab;
	double		a;
	double		b;
	double		c;
	double		d;

	if (cyl == NULL || ab2 == NULL)
		return (get_inf());
	ab = d3_minus(cyl->top, cyl->pos);
	*ab2 = d3_dot_product(ab, ab);
	a = d3_dot_product(v_x_ab, v_x_ab);
	b = 2.0 * d3_dot_product(v_x_ab, ao_x_ab);
	c = d3_dot_product(ao_x_ab, ao_x_ab) - (cyl->r * cyl->r * (*ab2));
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (get_inf());
	return ((-b - sqrt(d)) / (2 * a));
}

t_double3		trace_cyl(t_double3 orig, t_double3 dir, t_base_fig_cyl *cyl)
{
	t_double3	ao;
	t_double3	ab;
	t_double3	ao_x_ab;
	t_double3	v_x_ab;
	double		ab2;
	double		t;
	t_double3	i_pos;
	t_double3	i_pos_len;
	double		t_lim;

	if (cyl == NULL)
		return (d3_get_inf());
	dir = d3_normalize(dir);
	ab = d3_minus(cyl->top, cyl->pos);
	ao = d3_minus(orig, cyl->pos);
	ao_x_ab = d3_vector_product(ao, ab);
	v_x_ab = d3_vector_product(dir, ab);

	t = get_t(cyl, ao_x_ab, v_x_ab, &ab2);
	if (t == get_inf())
	{
		//only null
		return (d3_get_inf());
	}
	else if (t < 0)
	{
		//do shit to check caps
		return (d3_get_inf());
	}

	i_pos     = d3_plus(d3_mult(dir, t), orig);
	i_pos_len = d3_minus(i_pos, cyl->pos);
	t_lim     = d3_dot_product(i_pos_len, ab) / ab2;

	if (t_lim >= 0 && t_lim <= 1)
	{
		return (i_pos);
	}
	return (d3_get_inf());
}

/*
** cyl->top = (t_double3){0.0, 0.0, 1.0};
** cyl->pos = (t_double3){0.0, 0.0, -1.0};
*/

t_base_fig_cyl		*fig_cyl_create(void)
{
	t_base_fig_cyl		*cyl;

	if ((cyl = (t_base_fig_cyl*)malloc(sizeof(t_base_fig_cyl)))
																	== NULL)
		return (ft_puterr_null(1, "fig_cyl_create(): cannot "
		"malloc scene struct"));
	cyl->type = FIG_CYLINDER;
	cyl->top = (t_double3){4.0, 0.0, 1.0};
	cyl->pos = (t_double3){3.0, 0.0, -1.0};
	cyl->r = 1;
	cyl->col = color(128, 128, 128);
	return (cyl);
}