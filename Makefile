# ↓ Basic variables
CC := gcc -std=gnu11
CFLAGS :=  -std=gnu11 -W -Wall -Wextra -Wunused -Wpedantic
CFLAGS += -Wundef -Wshadow -Wcast-align
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += -Wcast-qual
CFLAGS += -Wunreachable-code
CFLAGS += -U_FORTIFY_SOURCE
CFLAGS += -iquote ./include
CFLAGS += -Ofast -march=native -mtune=native
LDFLAGS ?=

# ↓ CSFML
LDFLAGS += -lm
LDFLAGS += -lcsfml-window
LDFLAGS += -lcsfml-system
LDFLAGS += -lcsfml-graphics
LDFLAGS += -lcsfml-audio

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

.DEFAULT_GOAL := all
.PHONY: all
all: $(NAME)

# ↓ Compiling
$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# ↓ Cleaning
.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) -r $(BUILD_DIR)
	$(RM) $(NAME)


.NOTPARALLEL: re
.PHONY: re
re: fclean all

.PHONY: install
install: PREFIX ?= /usr/local/bin
install: $(NAME)
	install -D $< $(PREFIX)/$< --mode 0755

-include $(DEPS)
