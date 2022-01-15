# Makefile that compiles all the previous functions and archives them into a static library for future use
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -I. -lssl -lcrypto
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
STATIC = libhblk_crypto.a

.PHONY: $(STATIC)
$(STATIC): $(OBJ)
	$(AR) r $@ $(OBJ)
