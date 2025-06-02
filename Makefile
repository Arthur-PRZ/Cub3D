CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCDIR = src/
OBJDIR = obj/
LIBFTDIR = libft

SRC_FILES = main input_management utils get_map
SRC = $(addprefix $(SRCDIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJDIR), $(addsuffix .o, $(SRC_FILES)))
NAME = Cub3D
LIBFT = $(LIBFTDIR)/libftprintf.a

G = \033[1;92m
RST = \033[0m

all: $(OBJDIR) $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFTDIR) -lftprintf -lreadline -ltermcap
	@echo "$(G)Compilation done!$(RST)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(G)Compiling..$(RST)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIBFT):
	@make --no-print-directory -C $(LIBFTDIR)

clean:
	@rm -rf $(OBJDIR)
	@make clean --no-print-directory -C $(LIBFTDIR)
	@echo "$(G)Cleaned OBJ files$(RST)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean --no-print-directory -C $(LIBFTDIR)
	@echo "$(G)All clean$(RST)"

re: fclean all
	@echo "$(G)Cleaned and Compiled$(RST)"

.PHONY: all clean fclean re
