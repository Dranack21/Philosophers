######### COLORS ########
GREEN := $(shell printf "\033[32m")
RED := $(shell printf "\033[31m")
RESET := $(shell printf "\033[0m")

######### FLAGS ########
CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread
SANITIZE_FLAGS = -fsanitize=thread -fno-omit-frame-pointer

######### DIRECTORIES ########
SRC_DIR = srcs
OBJ_DIR = objs
INCLUDE_DIR = includes

INCLUDE_DIRS = -I$(INCLUDE_DIR)

######### FILES ########

SRC_FILES = $(SRC_DIR)/monitoring.c \
			$(SRC_DIR)/philo.c \
			$(SRC_DIR)/philo_life.c \
			$(SRC_DIR)/thread_utils.c \
			$(SRC_DIR)/monitoring.c \
			$(SRC_DIR)/utils.c \

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ_FILES_ASAN = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/asan/%.o,$(SRC_FILES))

######### NAME ########
NAME = philo
NAME_ASAN = asan_philo

######### COMMANDS ########
all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo -e "$(GREEN)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^
	@echo -e "$(GREEN)✓ $(NAME) successfully compiled!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<
	@printf "$(GREEN)█$(RESET)"

asan: $(NAME_ASAN)

$(NAME_ASAN): $(OBJ_FILES_ASAN)
	@echo -e "$(GREEN)Compiling $(NAME) with AddressSanitizer...$(RESET)"
	@$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -o $@ $^
	@echo -e "$(GREEN)✓ $(NAME) with ASAN successfully compiled!$(RESET)"
	@echo -e "$(GREEN)→ Run with: ASAN_OPTIONS=abort_on_error=1:halt_on_error=1 ./$(NAME_ASAN)$(RESET)"

$(OBJ_DIR)/asan/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(INCLUDE_DIRS) -c -o $@ $<
	@printf "$(GREEN)█$(RESET)"

clean:
	@echo -e "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo -e "$(RED)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo -e "$(RED)Removing executable...$(RESET)"
	@rm -f $(NAME) $(NAME_ASAN)
	@echo -e "$(RED)✓ Executable removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re asan