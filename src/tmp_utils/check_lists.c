/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:46:14 by snagat            #+#    #+#             */
/*   Updated: 2022/06/02 11:06:16 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdio.h>


void	ft_check_lists(t_lnode  *head)
{
	t_lnode		*current;

	current = head;

	while (current)
	{
		printf("[token = %s] [cmd = %s]\n", enum_to_str(current->type.token), current->type.cmd);
		current = current->next;
	}
}