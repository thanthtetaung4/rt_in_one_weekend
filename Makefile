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

INCLUDE = -I$(MLX_PATH) -I$(LIBFT_PATH) -Iinc -Isrc/gnl -Isrc/vec3
# Source and object files
DEFAULT = ./src
UTILS = $(DEFAULT)/utils
VEC3 = $(DEFAULT)/vec3
GNL = $(DEFAULT)/gnl/gnl.c
PARSING = $(DEFAULT)/parsing
ITEMS = ${DEFAULT}/items

SRCS = $(GNL) $(DEFAULT)/main.c $(DEFAULT)/ray.c \
		$(VEC3)/vec3.c $(VEC3)/vec3_ops.c $(VEC3)/vec3_scale.c \
		$(ITEMS)/sphere.c $(ITEMS)/plane.c $(ITEMS)/cylinder.c $(ITEMS)/cylinder_intersect.c \
		$(UTILS)/mlx_utils.c $(UTILS)/color_utils.c \
		$(UTILS)/camera_utils.c $(UTILS)/ray_utils.c $(UTILS)/math_utils.c \
		$(UTILS)/lighting_utils.c $(UTILS)/scene_utils.c $(UTILS)/error_utils.c \
		$(PARSING)/parser_utils.c $(PARSING)/parser.c $(PARSING)/material_parser.c \
		$(PARSING)/ambient_parser.c $(PARSING)/light_parser.c \
		$(PARSING)/camera_parser.c $(PARSING)/sphere_parser.c $(PARSING)/cylinder_parser.c \
		$(PARSING)/plane_parser.c $(UTILS)/print_obj.c $(UTILS)/print_world.c $(UTILS)/print_misc.c \
		$(PARSING)/ratio_parser.c $(PARSING)/init_scene.c $(UTILS)/shadow_utils.c \
		$(UTILS)/light_position_check.c $(UTILS)/camera_position_check.c $(PARSING)/check_rt.c
OBJS = $(SRCS:.c=.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Executable names
NAME = miniRT

# Rules
all: $(NAME)
	 @echo "\033[32m[$(NAME) is ready for use]\033[0m"

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
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	# @$(MAKE) -C $(MLX_PATH) fclean
	@echo "\033[35m[Fully cleaned up]\033[0m"

# Recompile everything
re: fclean all

# Compile .o files
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: all clean fclean re
