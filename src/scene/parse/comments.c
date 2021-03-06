/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_comments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 12:01:12 by hush              #+#    #+#             */
/*   Updated: 2020/06/17 23:19:00 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			*comments_delete(char *str)
{
	size_t		i;
	size_t		comments_len;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if ((comments_len = comments_skip_num(&str[i])) > 0)
		{
			ft_strcpy(&(str[i]), &(str[i + comments_len]));
		}
		i++;
	}
	return (str);
}

static int		comments_skip_num_loop(t_bool *comment_single,
	t_bool *comment_multiple, const char *str, size_t *i)
{
	if (comment_multiple == NULL || comment_single == NULL
	|| str == NULL || i == NULL)
		return (-1);
	if (*comment_single && str[*i] == '\n')
		*comment_single = FALSE;
	if (!ft_is_blank(str[*i]))
	{
		if (!(*comment_single) && !(*comment_multiple) && str[*i] == '/')
		{
			if (str[*i + 1] == '*')
				*comment_multiple = TRUE;
			else if (str[*i + 1] == '/')
				*comment_single = TRUE;
			else
				return (1);
			(*i)++;
		}
		if ((*comment_multiple) && str[*i] == '*')
			if (str[*i + 1] == '/')
			{
				*comment_multiple = FALSE;
				(*i)++;
			}
	}
	return (0);
}

size_t			comments_skip_num(const char *str)
{
	t_bool		comment_single;
	t_bool		comment_multiple;
	size_t		i;

	i = 0;
	comment_single = FALSE;
	comment_multiple = FALSE;
	while (str[i] != '\0')
	{
		if (!comment_multiple && !comment_single && str[i] != '/'
		&& !ft_is_blank(str[i]))
			break ;
		if (comments_skip_num_loop(&comment_single,
			&comment_multiple, str, &i) != 0)
			break ;
		i++;
	}
	return (i);
}
