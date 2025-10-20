# Program name
NAME = PmergeMe

# Compiler and flags
CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Directories
OBJDIR = obj

RESET  = \033[0m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m

# Source files
SRCS = main.cpp \

# Object files inside obj/
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# Default target
all: $(NAME)
	@echo "$(BLUE)Welcome to EX02 of CPP09$(RESET)"

# Link step
$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

# Compile step (pattern rule)
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling [$<]...$(RESET)"
	@$(CC) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN)Finished [$@]$(RESET)"

# Clean object files
clean:
	@if [ -d "$(OBJDIR)" ]; then \
		rm -rf $(OBJDIR); \
		echo "$(BLUE)Deleting all objects from /ex02...$(RESET)"; \
	else \
		echo "No objects to remove from /ex02."; \
	fi

# Full clean
fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "$(BLUE)Deleting $(NAME) from ex02...$(RESET)"; \
	else \
		echo "No Executable to remove from ex02."; \
	fi

# Rebuild
re: fclean all

.PHONY: all clean fclean re