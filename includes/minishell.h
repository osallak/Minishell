/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:31:59 by osallak           #+#    #+#             */
/*   Updated: 2022/04/24 18:12:34 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include "gc.h"
# include "../printf_err/ft_printf.h"

typedef enum tokens
{
	WORD,
	PIPE,
	OUTRED,
	INRED,
	APPEND,
	HERDOC,
	AND,
	OR,
	SPACE,
	OBRACKET,
	CBRACKET,
	SQUOTE,
	DQUOTE,
	BG,
	VAR,
}	t_tokens_flag;

typedef struct s_tokens
{
	char			*token;
	int				flag;
	struct s_tokens	*next;
	struct s_tokens	*previous;
}	t_tokens;

//pcn stands for previous, current and next
typedef struct s_pcn_flags
{
	int				prev;
	int				curr;
	int				next;
}	t_pcn_flags;

extern t_gc	*g_garbage;

// double linked list
t_tokens	*node_del_dll(t_tokens **dll, t_tokens *node);
void		del_dll(t_tokens **dll);
t_tokens	*init_list_dll(char *input, int flag);
void		add_back_dll(t_tokens **tokens_list, t_tokens *new);

//tokenizer functions
t_tokens	*init_list_dll(char *input, int flag);
void		add_back_dll(t_tokens **tokens_list, t_tokens *new);
t_tokens	*tokenizer(char *input);
int			get_tokens(t_tokens **head, char *input, int len, int flag);
int			tokenize_word(t_tokens **head, char *input, int flag);
int			tokenize_space(t_tokens **head, char *input);
int			tokenize_quotes(t_tokens **head, char *input);
int			tokenize_variables(t_tokens **head, char *input);
bool		isword(int c);
//parsing functions
void		isbalanced_brackets(t_tokens *head);
void		isbalanced_quotes(t_tokens *head);
void		syntax_analyser(t_tokens *tokens);
void		check_red_tokens(t_tokens *tokens);
void		check_opar(t_tokens *tokens);
void		check_cpar(t_tokens *tokens);
bool		is_string(int flag);
bool		isredirect(int flag);
void		print_syntax_error(char *error);
void		init_flags(t_pcn_flags *flags, t_tokens *tokens);
void		check_cpar_left(t_tokens *tokens);
void		check_cpar_right(t_tokens *tokens);
void 		check_opar_left(t_tokens *tokens);
void 		check_opar_right(t_tokens *tokens);
#endif