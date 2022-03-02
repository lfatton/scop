.PHONY: all, run, clean, re

NAME = scop

SRC_PATH = srcs

SRC_NAME = main.cpp

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

LDFLAGS = -lglfw -lvulkan

CC = g++

CFLAGS = -std=c++17 -O2

RM = rm -rf

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $@

run: $(NAME)
	./$(NAME)

clean:
	$(RM) $(NAME)

re: clean all