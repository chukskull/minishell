
#include "parser.h"
#include "minishell.h"
#include "lexer.h"

char *convert_token(e_token token)
{
	if (token == SGLQT)
		return ("'");
	else if (token == DBLQT)
		return ("\"");
	else if (token == REDRO)
		return (">");
	else if (token == REDRI)
		return ("<");
	else if (token == DLMI)
		return ("<<");
	else if (token == APPND)
		return (">>");
	else if (token == PIPE)
		return ("|");
	else if (token == SPC)
		return (" ");
	else if (token == AND)
		return ("&&");
	else if (token == OR)
		return ("||");
	else if (token == CMD)
		return ("CMD");
	else if (token == EOL)
		return ("EOL");
	else if (token == DLR)
		return ("$");
	else if (token == LEFT_PAR)
		return ("(");
	else if (token == RIGHT_PAR)
		return (")");
	return (NULL);
}

int count_token(t_lnode *head, t_lnode *current, e_token t)
{
	int count;

	count = 0;
	while (head != current)
	{
		if (get_token(head) == t)
			count++;
		head = head->next;
	}
	return (count);
}

static void n_free_leaks(t_lnode *p, t_lnode *current)
{
	t_lnode *tmp;

	while (p != current)
	{
		tmp = p->next;
		free_lexer_node(p);
		p = tmp;
	}
}
static void norm_join_quote(t_lnode *current, t_lnode *node)
{
	if (get_token(current) == CMD)
	{
		set_cmd(node, ft_strjoin(get_cmd(node), get_cmd(current), 2));
		set_cmd(current, NULL);
	}
	else
		set_cmd(node, ft_strjoin(get_cmd(node),
								 convert_token(get_token(current)), 0));
}

t_lnode *handle_quote(t_lnode *head, e_token dlm)
{
	t_lnode *current;
	t_lnode *sg;
	t_lnode *node;
	t_lnode *p;

	current = head;
	node = ft_new_node_lex(CMD, "");
	sg = current;
	current = current->next;
	while (get_token(current) != dlm && get_token(current) != EOL)
	{
		norm_join_quote(current, node);
		current = current->next;
	}
	if (get_token(current) == EOL)
	{
		printf("Can not find a %s ender!\n", convert_token(dlm));
		free_lexer_node(node);
		return (t_lnode *)(-1);
	}
	p = sg->next;
	n_free_leaks(p, current);
	sg->next = node;
	node->next = current;
	return current->next;
}

static t_lnode *check_sglqt_dblqt(t_lnode *current, t_lnode *node)
{
	while ((get_token(current) == SGLQT || get_token(current) == DBLQT))
	{
		if (get_token(current->next) == CMD)
		{
			set_cmd(node, ft_strjoin(get_cmd(node),
									 get_cmd(current->next), 2));
			current = current->next->next;
		}
		else if ((get_token(current) == SGLQT || get_token(current) == DBLQT) && (get_token(current->next) == DBLQT || get_token(current->next) == SGLQT))
			current = current->next;
		else if ((get_token(current) == SGLQT || get_token(current) == DBLQT) && get_token(current->next) != CMD)
			break;
		else if ((get_token(current) == SGLQT || get_token(current) == DBLQT))
			current = current->next;
	}
	return (current);
}

static void free_quotes_leaks(t_lnode *temp, t_lnode *current)
{
	t_lnode *tm;

	while (temp != current)
	{
		tm = temp->next;
		free(temp);
		temp = tm;
	}
}

void join_quotes(t_lnode *head)
{
	t_lnode *p;
	t_lnode *current;
	t_lnode *temp;
	t_lnode *node;

	current = head;
	while (current)
	{
		if (((get_token(current) == SGLQT || get_token(current) == DBLQT)
		&& get_token(current->next) == CMD))
		{
			node = ft_new_node_lex(CMD, "");
			p = current;
			current = check_sglqt_dblqt(current, node);
			temp = p->next;
			free_quotes_leaks(temp, current);
			p->next = node;
			node->next = current;
		}
		current = current->next;
	}
}

t_lnode *handle_single_quote(t_lnode *head)
{
	return handle_quote(head, SGLQT);
}

static void	n_check_cur_head(t_lnode **head, t_lnode *current, t_lnode *prev,
		t_lnode *node)
{
	if (current == *head)
	{
		*head = current->next;
		(*head)->next = node;
	}
	else
	{
		prev->next = current->next;
		prev->next->next = node;
	}
}
void join_cmd_with_quotes(t_lnode **head)
{
	t_lnode *current;
	t_lnode *node;
	t_lnode *prev;
	t_lnode *tmp;

	prev = NULL;
	current = *head;
	while (current)
	{
		if (current && current->next && current->next->next
			&& get_token(current) == CMD && (get_token(current->next) == SGLQT
			|| get_token(current->next) == DBLQT)
			&& get_token(current->next->next) == CMD)
		{
			node = ft_new_node_lex(CMD, get_cmd(current));
			n_check_cur_head(head, current, prev, node);
			set_cmd(node, ft_strjoin(get_cmd(node),
									 get_cmd(current->next->next), 2));
			tmp = current->next->next;
			node->next = tmp->next;
			free(tmp);
		}
		prev = current;
		current = current->next;
	}
}
