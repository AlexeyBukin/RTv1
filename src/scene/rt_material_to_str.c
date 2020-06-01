/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_scene_material.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 16:58:34 by hush              #+#    #+#             */
/*   Updated: 2020/06/01 03:57:16 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char				*material_to_str(t_material *material)
{
	char 	*res;

	if (material == NULL)
		return (ft_puterr_null(1, "plain_to_str(): NULL pointer"));
	res = ft_strdup("material[");
	res = ft_strjoin_free(res, ft_lltoa(material->id));
	res = ft_str_add(res, "]( color:");
	res = ft_strjoin_free(res, col_to_str_color(material->col));
	res = ft_str_add(res, ", roughness:");
	res = ft_strjoin_free(res, ft_ldtoa(material->pbr.PBR_ROUGHNESS));
	res = ft_str_add(res, ", metallic:");
	res = ft_strjoin_free(res, ft_ldtoa(material->pbr.PBR_METALLIC));
	res = ft_str_add(res, ", specular:");
	res = ft_strjoin_free(res, ft_ldtoa(material->pbr.PBR_SPECULAR));
	res = ft_str_add(res, ")");
	return (res);
}
