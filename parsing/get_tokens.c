/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:07:25 by osallak           #+#    #+#             */
/*   Updated: 2022/03/31 10:13:53 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens(t_tokens **head, char *input)
{
	if (input[1] == '|')
	{
		add_back_dll(head, init_list_dll(collect(ft_strdup("||")), OR));
		input++;
	}
	else
		add_back_dll(head, init_list_dll(collect(ft_strdup("|")), PIPE));
	input++;
}

