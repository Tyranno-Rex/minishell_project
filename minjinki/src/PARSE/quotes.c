/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:24:44 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/23 14:57:03 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** parsing phase one
**	: split by quotes
** 
** e.g. ls -al "hi"'hello' "take me home" TT T
**	>> `ls -al `, `hi`,  `hello`,   ` `, `take me home`, ` TT T`-> data
**	>>	(STR), (DOUBLE), (SINGLE), (STR), (DOUBLE),      (STR)	-> type
** string between ` saved. ` is not saved
*/

t_token	*malloc_node(void)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		ft_lstclear(&(g_glob.tok));
		print_error("Fail to allocate memory: t_token\n");
		return (NULL);
	}
	return (new);
}

t_token	*add_node(int type, int len, char *start)
{
	t_token	*new;

	new = malloc_node();
	new->type = type;
	new->data = ft_strndup(start, len);
	if (!(new->data))
	{
		print_error("Fail to allocate memory: t_token.data\n");
		return (NULL);
	}
	return (new);
}

/*
** ft_strnlen()
**	returns the length before a given char
**	returns ERROR(-1) if there is no char
*/
int	quotes(int type, char *cmd)
{
	int	len;

	len = ft_strnlen(cmd + 1, type);
	if (len == ERROR)
	{
		ft_lstclear(&(g_glob.tok));
		print_error("syntax error: unclosed quotes\n");
		return (ERROR);
	}
	ft_lstadd_back(&(g_glob.tok), add_node(type, len, cmd + 1));
	return (len);
}

/*
** split_quote()
**	first step of tokenization
** 	split by quotes
** 
** if (cmd != quote)
**	to execute quotes() immediatly
**	when openning quote appears very next to closing quote.
** 
** ERROR: to deal unclosed quote
** 
** end == index of closing quote
** I tried to return end + 1 but it doesn't work well🤔
*/
int	split_quote(int len, char *cmd, char *quote)
{
	int	end;

	end = 0;
	if (cmd != quote)
		ft_lstadd_back(&(g_glob.tok), add_node(STR, len, cmd));
	if (*quote == SINGLE)
		end = quotes(SINGLE, quote);
	else if (*quote == DOUBLE)
		end = quotes(DOUBLE, quote);
	if (end == ERROR)
		return (ERROR);
	return (end);
}

void	deal_quotes(char *cmd)
{
	int		i;
	int		gap;
	int		last;
	char	*start;

	i = -1;
	last = 0;
	start = cmd;
	while (cmd[++i])
	{
		if (cmd[i] == SINGLE || cmd[i] == DOUBLE)
		{
			gap = split_quote(i - last, start, cmd + i);
			if (gap == ERROR)
				return ;
			i += (gap + 1);
			start = cmd + i + 1;
			last = i + 1;
		}
	}
	if (start == cmd)
		ft_lstadd_back(&(g_glob.tok), add_node(STR, i, cmd));
	if (*start)
		split_quote(i + 1, start, cmd);
}
