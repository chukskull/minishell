#include "minishell.h"

char *return_cmd_full_path(t_parsing_node *root, t_exec_struct *exec_s)
{
	char *p;

	if (root->cmd.cmd[0] != '/')
		p = check_if_bin_exist(root->cmd.cmd, exec_s->path);
	else
		p = root->cmd.cmd;
	return p;
}

pid_t spawn_process(int in, int out, t_parsing_node *root, t_exec_struct *exec_s, int *fd)
{
	pid_t pid;

	printf("Executing %s\n", root->cmd.cmd);
	pid = fork();
	if (pid == 0)
	{
		char *p;

		if (in != 0)
		{
			dup2(in, 0);
		   close(in);
		}
		if (out != 1)
		{ 
			dup2(out, 1);
		   close(out);
		}
		p = return_cmd_full_path(root ,exec_s);
		if (p == NULL)
			show_errno();
		close(fd[0]);
		close(fd[1]);
		execve(p, root->cmd.argv, exec_s->envp);
		exit(0);
	   
	}
	else
	{
		// waitpid(-1, 0, 0);
		if (in != 0)
		{
			close(in);
		}
			// close(in);
		if (out != 1)
			close(out);
		return (pid);
	}
}

void recursive_exec(t_parsing_node *node, t_exec_struct *exec_s)
{
	static int fd[2];
	int status;
	int pid2;
	int fd2;
	

	fd2 = dup(0);
	while (node->type == PIPE)
	{
		int ret = pipe(fd);
		if (ret < 0)
			exit(-1);
		spawn_process(0, fd[1], node->lchild, exec_s, fd);
		if (node->rchild->type == CMD)
		{
			pid2 = spawn_process(fd[0], 1, node->rchild, exec_s, fd);
			waitpid(pid2, &status, 0);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[0]);
		}
		node = node->rchild;
	}
	dup2(fd2, 0);
	close(fd2);
	while(waitpid(-1, &status, 0) != -1);
}


void	exec_simple_cmd(t_parsing_node *node, t_exec_struct *exec_s)
{
	pid_t	pid;
	char	*p;

	pid = fork();
	if (pid == 0)
	{
		p = return_cmd_full_path(node, exec_s);
		if (p == NULL)
			show_errno();
		handle_output_redirect(node);
		printf("%s\n", node->cmd.argv[0]);
		execve(p, node->cmd.argv, exec_s->envp);
		exit(0);
	}
	else
		wait(NULL);
	
}

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[])
{
	init(exec_s, envp);
	builtins(root);

	exec_simple_cmd(root, exec_s);
}