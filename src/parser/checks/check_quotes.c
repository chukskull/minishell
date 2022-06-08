/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:38:25 by snagat            #+#    #+#             */
/*   Updated: 2022/06/08 18:54:44 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int    ft_check_quotes(t_lnode *head, e_token dlm)
{
    t_lnode *current;

    current = head;
    while(current)
    {
        if (get_token(current) == dlm
            && current->next && current->next->next 
            && get_token(current->next) == CMD  && is_empty(get_cmd(current->next))
            && get_token(current->next->next) == EOL)
                return(FAIL);     
        current = current->next;
    }
    return(SUCCESS); 
}