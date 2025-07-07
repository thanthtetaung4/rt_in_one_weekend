#OS detection
UNAME := $(shell uname)

# Paths and Files
ifeq ($(UNAME), Darwin)
	MLX_PATH = ./mlx_metal
	MLX_LIB = $(MLX_PATH)/libmlx.dylib
	MLX_REPO = https://github.com/novailable/minilibx_metal.git
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework Metal -framework AppKit
else ifeq ($(UNAME), Linux)
	MLX_PATH = ./mlx
	MLX_LIB = $(MLX_PATH)/libmlx.a
	MLX_REPO = https://github.com/42Paris/minilibx-linux.git
	MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11
else
	$(error $(shell printf "\033[31mUnsupported OS: $(UNAME)\033[0m"))
endif

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

CFLAGS = #-Wall -Wextra -Werror

# Source and object files
DEFAULT = ./src
UTILS = $(DEFAULT)/utils
VEC3 = $(DEFAULT)/vec3
GNL = $(DEFAULT)/gnl/gnl.c

SRCS = $(GNL) $(DEFAULT)/main.c $(UTILS)/color_utils.c $(UTILS)/math_utils.c $(UTILS)/render_utils.c $(VEC3)/vec3.c $(UTILS)/camera_utils.c $(UTILS)/ray_utils.c $(UTILS)/lighting_utils.c $(UTILS)/scene_utils.c
OBJS = $(SRCS:.c=.o)

# BOX_SRCS = $(DEFAULT)/main_box.c $(UTILS)/color_utils.c $(UTILS)/math_utils.c $(UTILS)/render_utils.c $(VEC3)/vec3.c $(UTILS)/camera_utils.c $(UTILS)/ray_utils.c $(UTILS)/lighting_utils.c $(UTILS)/scene_utils.c
# BOX_OBJS = $(BOX_SRCS:.c=.o)

# PIPE_SRCS = $(DEFAULT)/main_pipe.c $(UTILS)/color_utils.c $(UTILS)/math_utils.c $(UTILS)/render_utils.c $(VEC3)/vec3.c $(UTILS)/camera_utils.c $(UTILS)/ray_utils.c $(UTILS)/lighting_utils.c $(UTILS)/scene_utils.c
# PIPE_OBJS = $(PIPE_SRCS:.c=.o)

# Compiler
CC = cc

# Executable names
NAME = rt
BOX_NAME = rt_box
PIPE_NAME = rt_pipe

# Rules
all: $(NAME) #$(BOX_NAME) $(PIPE_NAME)
	 @echo "\033[32m[$(NAME), $(BOX_NAME), and $(PIPE_NAME) are ready for use]\033[0m"

$(NAME): $(MLX_LIB) $(OBJS)  $(LIBFT)
	@echo "$(NAME) compiling..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_PATH) $(LIBFT) $(MLX_LIB) -lm -o $(NAME)

$(BOX_NAME): $(MLX_LIB) $(BOX_OBJS) $(LIBFT)
	@echo "$(BOX_NAME) compiling..."
	@$(CC) $(CFLAGS) $(BOX_OBJS) $(MLX_FLAGS) -L$(LIBFT_PATH) $(LIBFT) $(MLX_LIB) -lm -o $(BOX_NAME)

$(PIPE_NAME): $(MLX_LIB) $(PIPE_OBJS) $(LIBFT)
	@echo "$(PIPE_NAME) compiling..."
	@$(CC) $(CFLAGS) $(PIPE_OBJS) $(MLX_FLAGS) -L$(LIBFT_PATH) $(LIBFT) $(MLX_LIB) -lm -o $(PIPE_NAME)

# Clone and compile the MiniLibX library
$(MLX_LIB):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "\033[33m[Cloning MiniLibX...]\033[0m"; \
		git clone $(MLX_REPO) $(MLX_PATH); \
	fi
	@$(MAKE) -C $(MLX_PATH)

# Compile the libft library
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

# Clean object files
clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@echo "$(NAME) cleaning..."
	@rm -f $(OBJS)
	@rm -f $(BOX_OBJS)
	@rm -f $(PIPE_OBJS)
	@echo "\033[35m[Cleaned up]\033[0m"

# Clean object files and executable
fclean: clean
	@rm -f $(NAME) $(BOX_NAME) $(PIPE_NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	# @$(MAKE) -C $(MLX_PATH) fclean
	@echo "\033[35m[Fully cleaned up]\033[0m"

# Recompile everything
re: fclean all

# Compile .o files
%.o: %.c
	@$(CC) $(CFLAGS) -I$(MLX_PATH) -I$(LIBFT_PATH) -c $< -o $@

.PHONY: all clean fclean re
