#FIXME: We should add checks on the headers too.
CC=gcc
INC=inc/
FLAGS=-Wall -Wextra -Werror
MAIN= main_utils.c main.c
B_DIR= build
# If a new directory is created inside src, we should have it in a variable
# containing all files inside, and add it to CFILES too.
# DBGUTILS= $(addprefix dbg_utils/, token_str.c check_lists.c tree_debug.c visual_tree.c)
UTILS= $(addprefix utils/, ft_new_node.c node_operations_parse.c get_token.c get_cmd.c free_list.c\
		general_utils.c free_tree.c)
LEXERC=$(addprefix lexer/, lexing.c)
PARSERC=$(addprefix parser/, parser.c parser_utils.c)
PARSETREE=$(addprefix parser/main_tree/, main_tree.c main_tree_1.c analyze_cmd.c)
PARSQUOTES = $(addprefix parser/quotes/, handle_single_quotes.c  handle_single_quotes_1.c handle_single_quotes_2.c handle_double_quotes.c handle_quotes.c )
PARSCHECK= $(addprefix parser/checks/, check_quotes.c check_all.c two_nearby_tokens.c check_conditional.c check_paranthesis.c check_parenthesis_2.c) 
PARSRED= $(addprefix parser/redirections/, o_redr.c o_redr_1.c o_redr_2.c)
PARSENV= $(addprefix parser/expansion/, expand.c expand_1.c expand_2.c expand_3.c wildcard.c)
PARSEP=$(addprefix parser/parenthesis/, parse_parenthesis.c parse_parenthesis_1.c)
EXEC=$(addprefix exec/, exec.c exec_1.c exec_2.c exec_3.c gen_utils.c gen_utils_1.c error_handling.c reds_exec.c reds_exec_1.c or_and_exec.c change_exit_status.c bridge.c)
BUILTINS= $(addprefix exec/builtins/, check_builtins.c echo.c cd.c cd_1.c pwd.c env.c copy_env.c cd_utils.c exit.c ft_unset.c export.c export_1.c export_utils.c export_utils_1.c)
CFILES= $(addprefix src/, $(LEXERC) $(MAIN) $(UTILS) $(DBGUTILS) $(PARSCHECK) $(PARSQUOTES) $(PARSRED) $(PARSENV) $(PARSETREE) $(PARSEP) $(PARSERC) $(EXEC) $(BUILTINS))
OFILES=$(addprefix build/, $(CFILES:.c=.o))
LIBFT=libft/libft.a
PROGRAM= minishell

all: $(PROGRAM)

$(PROGRAM) : $(OFILES)
	@cd libft && make
	$(CC) $(FLAGS) $(LDFLAGS) $(CPPFLAGS) -g   $(OFILES) $(LIBFT) -I $(INC) -o $(PROGRAM) -lreadline
	
$(B_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(CPPFLAGS) -I $(INC) -g  -c $< -o $@

clean:
	rm -rf $(B_DIR)
	@cd libft && make fclean

fclean: clean
	rm  -f $(PROGRAM)

re: fclean all
