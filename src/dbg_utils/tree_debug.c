#include "parser.h"

void show_node(t_parsing_node *node)
{
	printf("--------------------------\n");
	if (node->type == CMD)
	{
		int i;
		printf("%s [", node->cmd.cmd);
		i = 0;
		while (node->cmd.argv[i])
			printf("%s, ", node->cmd.argv[i++]);
		printf("]\n");	
	}
	else
		printf("%s\n", enum_to_str(node->type));
	printf("--------------------------\n");
}

void inorder_show(t_parsing_node *root)
{
	if (root == NULL)
		return;
	inorder_show(root->lchild);
	show_node(root);
	inorder_show(root->rchild);
}