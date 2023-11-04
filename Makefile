# ↓ Basic variables
CC := gcc -std=gnu11
CFLAGS := -W -Wall -Wextra -Wunused -Wpedantic
CFLAGS += -Wundef -Wshadow -Wcast-align
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += -Wcast-qual
CFLAGS += -Wunreachable-code
CFLAGS += -U_FORTIFY_SOURCE
CFLAGS += -iquote ./include
CFLAGS += -Ofast -march=native -mtune=native -flto

# ↓ CSFML
CSFML_FLAGS := -lm
CSFML_FLAGS += -lcsfml-window
CSFML_FLAGS += -lcsfml-system
CSFML_FLAGS += -lcsfml-graphics
CSFML_FLAGS += -lcsfml-audio
CFLAGS += $(CSFML_FLAGS)

# ↓ Binaries
NAME := infiniteBalls

# Source files
VPATH := src
SRC := main.c
SRC += ball.c

# ↓ Objects
BUILD_DIR := .build
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

# ↓ Dependencies for headers
DEPS_FLAGS := -MMD -MP
DEPS := $(OBJ:.o=.d)

DIE := exit 1

all: $(NAME)

.PHONY: all

# ↓ Compiling
$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) || $(DIE)

.PHONY: $(NAME)

# ↓ Cleaning
clean:
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) -r $(BUILD_DIR)
	@ $(RM) $(NAME)

.PHONY: clean fclean

re: fclean all

.PHONY: re

-include $(DEPS)
