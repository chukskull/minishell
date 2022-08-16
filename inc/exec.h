#include "minishell.h"

#ifndef EXEC_H
# define EXEC_H

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[]);
void free_charpp(char **p);
char *get_env(char *var, void* exec_s, int flag);
char *check_if_bin_exist(char *bin_name, char *path_env);

char **show_envp(char *envp[]);
void init(t_exec_struct *exec_s, char *envp[]);
int show_errno();

int is_input_redirected(t_parsing_node *node);
int is_output_redirected(t_parsing_node *node);
int is_heredoc(t_parsing_node *node);
int is_append(t_parsing_node *node);
int handle_output_redirect(t_parsing_node *node);
int handle_herdoc(t_parsing_node *node, t_exec_struct *exec_s);
int handle_append(t_parsing_node *node);
int handle_append_oredr(t_parsing_node *node);
int handle_herdoc_iredr(t_parsing_node *node, t_exec_struct *exec_s);
int	exec_simple_cmd(t_parsing_node *node, t_exec_struct *exec_s);
void pipe_chain_exec(t_parsing_node *node, t_exec_struct *exec_s);
void and_chain_exec(t_parsing_node *node, t_exec_struct *exec_s);
void or_chain_exec(t_parsing_node *node, t_exec_struct *exec_s);


# endif