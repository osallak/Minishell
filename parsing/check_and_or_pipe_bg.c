/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_or_pipe_bg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:57:47 by osallak           #+#    #+#             */
/*   Updated: 2022/04/25 16:22:54 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_or_pipe_bg_left(t_tokens *tokens)
{
	int	pre_flag;
	int	status;

	pre_flag = -1;
	status = 0;
	if (!tokens->previous
		|| (tokens->previous->flag == SPACE && !tokens->previous->previous))
		status = 2;
	else if (tokens->previous->flag)
		pre_flag = tokens->previous->previous->flag;
	else
		pre_flag = tokens->previous->flag;
	if (!is_string(pre_flag) && pre_flag != CBRACKET)
		status = 2;
	if (status == 2)
		print_syntax_error(tokens->token);
	set_status(status);
}

void	check_and_or_pipe_bg_right(t_tokens *tokens)
{
	int	next;
	int	status;
	int	tmp;

	tmp = 0;
	status = 0;
	next = -1;
	if ((!tokens->next || (tokens->next->flag == SPACE && !tokens->next->next)))
	{
		if (tokens->flag == BG)
			tmp = 1;
		else
			status = 2;
	}
	else if (tokens->next->flag == SPACE)
		next = tokens->next->next->flag;
	else
		next = tokens->next->flag;
	if (!is_string(next) && !isredirect(next) && next != OBRACKET)
		status = 2;
	if (tmp)
		status = 0;
	if (status == 2)
		print_syntax_error(tokens->token);
	set_status(status);
}

void	check_and_or_pipe_bg(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->flag >= PIPE && tokens->flag <= BG)
		{
			check_and_or_pipe_bg_left(tokens);
			if (!g_global.exit_status)
				check_and_or_pipe_bg_right(tokens);
			if (g_global.exit_status)
				break ;
		}
		tokens = tokens->next;
	}
}