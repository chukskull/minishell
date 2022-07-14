/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:23:48 by snagat            #+#    #+#             */
/*   Updated: 2022/06/20 14:56:55 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

// Here CMD type stands for STRING in general for example
// cat flag.txt cat is a command but flag.txt is a string.

typedef enum {
	SGLQT, 
	DBLQT, 
	REDRI,
	REDRO,
	DLMI,
	APPND,
	PIPE,
	CMD, 
	EOL,
	SPC, 
	RPAR,
	LPAR,
	OR,
	AND,
	DLR,
	LEFT_PAR, 
	RIGHT_PAR, 
} e_token;

typedef	struct s_type
{
	e_token	token;
	char	*cmd;
} t_type;


typedef struct s_lexer_node
{
	struct s_lexer_node	*next;
	t_type				type;
} t_lnode;

t_lnode	*ft_lexer(char *str);
t_lnode	*ft_new_node_lex(e_token token, char *cmd);
t_lnode	*ft_add_back_lex(t_lnode **head, e_token token, char *cmd);
e_token	lexer_get_type(char a, char b);
char    *enum_to_str(e_token   token);
void    ft_check_lists(t_lnode  *head);
void set_token(t_lnode *node, e_token e);
void    set_cmd(t_lnode *node, char *cmd);
char    *get_cmd(t_lnode *node);
e_token get_token(t_lnode *node);
void free_lexer_node(t_lnode *node);
t_lnode *lex(char *cmd);



# endif