/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_merge_n_split_nodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:15:48 by minjinki          #+#    #+#             */
/*   Updated: 2023/05/11 15:31:30 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	merge_nodes(t_token *cur)
{
	while (cur && cur->next)
	{
		if ((cur->type == STR || cur->type == DOUBLE || cur->type == SINGLE)
			&& (cur->next->type == STR
				|| cur->next->type == DOUBLE || cur->next->type == SINGLE))
		{
			cur->data = do_join(cur->data, cur->next->data);
			if (!(cur->data))
				return (FALSE);
			ft_lstremove(cur, cur->next);
		}
		else
			cur = cur->next;
	}
	return (TRUE);
}

t_bool	split_node(t_token **new_tok, t_token *cur)
{
	int		i;
	char	*data;
	char	**matrix;
	t_token	*new;

	matrix = ft_split(cur->data, ' ');
	if (!matrix)
		return (FALSE);
	i = -1;
	while (matrix[++i])
	{
		data = ft_strdup(matrix[i]);
		new = ft_lstnew(STR, data);
		if (!new)
			return (FALSE);
		ft_lstadd_back(new_tok, new);
	}
	free_matrix(matrix);
	return (TRUE);
}

void	rm_last_spaces(t_token **tok)
{
	t_token *cur;
	t_token	*pre;

	pre = NULL;
	cur = *tok;
	while (cur->next)
	{
		pre = cur;
		cur = cur->next;
	}
	if (cur->type == SPACES)
	{
		pre->next = NULL;
		ft_lstdelone(cur);
	}
}

t_bool	merge_n_split_nodes(t_token **tok)
{
	t_token	*new;
	t_token	*cur;

	new = NULL;
	cur = *tok;
	merge_nodes(*tok);
	// while (cur)
	// {
	// 	if (!split_node(&new, cur))
	// 		return (FALSE);
	// 	cur = cur->next;
	// }
	// ft_lstclear(&(g_glob.tok));
	// g_glob.tok = new;
	rm_last_spaces(&(g_glob.tok));
	return (TRUE);
}
