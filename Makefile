NAME = minishell

CC = cc

CFLAGS = -Werror -Wall -Wextra  -I./include/ #-g3 -fsanitize=address

SRC = parsing/expansion/expander.c parsing/expansion/expansion_helper.c parsing/expansion/ft_expansion_splitter.c parsing/expansion/utils.c parsing/expansion/utils2.c \
	parsing/lexer/lexer.c parsing/lexer/lexer_quotes.c parsing/lexer/lexer_quotesII.c parsing/lexer/tokenize_lexer.c parsing/syntax/syntax.c parsing/syntax/syntax_checker.c \
	parsing/tokenizer.c parsing/sanitize_inputs.c parsing/quotes.c parsing/parser/parser.c parsing/parser/parser_command.c parsing/parser/parser_redirs.c parsing/parser/parser_utils.c\
	others/MiniLibc/strings/ft_bzero.c others/MiniLibc/strings/ft_calloc.c others/MiniLibc/strings/ft_itoa.c others/MiniLibc/strings/ft_memcpy.c \
	others/MiniLibc/strings/ft_memset.c others/MiniLibc/strings/ft_split.c others/MiniLibc/strings/ft_strchr.c others/MiniLibc/strings/ft_strcmp.c \
	others/MiniLibc/strings/ft_strcpy.c others/MiniLibc/strings/ft_strdup.c others/MiniLibc/strings/ft_strjoin.c others/MiniLibc/strings/ft_atoi.c \
	others/MiniLibc/strings/ft_strlen.c others/MiniLibc/strings/ft_strstr.c others/MiniLibc/strings/ft_substr.c others/MiniLibc/ctypes/isalnum.c \
	others/MiniLibc/ctypes/isalpha.c others/MiniLibc/ctypes/isascii.c others/MiniLibc/ctypes/isdigit.c others/MiniLibc/ctypes/isspace.c \
	others/garbage_collector/garbage_collector.c others/garbage_collector/garbage_collector_helper.c others/MiniLibc/ft_printf/ft_printf.c \
	others/MiniLibc/ft_printf/ft_putchar.c others/MiniLibc/ft_printf/ft_putcherx.c \
	others/MiniLibc/ft_printf/ft_puthex.c others/MiniLibc/ft_printf/ft_putnbr.c others/MiniLibc/ft_printf/ft_putptr.c others/MiniLibc/ft_printf/ft_putstr.c \
	others/MiniLibc/ft_printf/ft_spf.c others/MiniLibc/ft_printf/ft_unsigned.c others/envadd.c execution/heredoc.c others/signals.c parsing/utils.c \
	execution/builtins/builtins_utils.c execution/builtins/cd.c execution/builtins/cd_utils.c execution/builtins/echo.c execution/builtins/env.c execution/builtins/export.c execution/builtins/export_utils.c execution/builtins/export_utils_II.c execution/builtins/export_utils_III.c execution/builtins/exit.c \
	execution/builtins/pwd.c execution/builtins/unset.c execution/redirections/redirects_io.c execution/executer.c execution/executer_helper.c execution/executer_helper_II.c execution/execution_utils.c

OBJ = $(SRC:%.c=%.o) 

all : $(NAME)

$(NAME) : $(OBJ) $(SRC)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -I./others/ft_printf/ main.c -o $(NAME)
clean :
	@rm -rf $(OBJ) 
	@echo "\033[0;31mremoving obj files\033[0m"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[0;31mremoving archives and executables\033[0m"

re : fclean all

.PHONY : re all clean fclean

.SECONDARY : $(OBJ) $(NAME)
