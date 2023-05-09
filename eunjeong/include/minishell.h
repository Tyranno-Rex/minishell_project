/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjinki <minjinki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:20:32 by minjinki          #+#    #+#             */
/*   Updated: 2023/03/16 17:02:17 by minjinki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


// minjinki
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "define.h"
# include "env.h"
# include "parse.h"
# include "structs.h"
# include "utils.h"
# include "../src/LIBFT/libft.h"

// eunjeong
# include <signal.h>
# include <sys/types.h>
# include <string.h>
# include <stdbool.h>
# include <termios.h>
# include <fcntl.h>
# include "signal.h"
# include "builtin.h"
# include "pipe.h"

t_glob	g_glob;
int	    check_single_builtin();
char    **make_tok2D(void);
void	save_origin_io(int origin_io[2]);
void	restore_origin_io(int origin_io[2]);
int	    do_redirect(t_token *proc_data);

#endif