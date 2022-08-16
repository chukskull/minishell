/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:16:36 by snagat            #+#    #+#             */
/*   Updated: 2022/08/15 22:39:41 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"


void free_lexer_node(t_lnode *node)
{
    if (get_cmd(node))
        free(get_cmd(node));
    free(node);
}

void    free_list(t_lnode **head)
{
    t_lnode *current;
    t_lnode *tmp;

    current = *head;
    if (head == 0 || *head == 0)
        return ;
    while(current)
    {
        tmp = current;
        if (tmp->type.cmd)
            free(tmp->type.cmd);
        current = current->next;
        free(tmp);
    }
    *head = 0;
}

void free_all(char *cmd, t_lnode *head, t_parsing_node *root)
{
    (void)head;
    free_list(&head);
	free_tree(root);
	free(cmd);
}