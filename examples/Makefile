CFLAGS=-W -Wall -Wextra -Werror -g -std=c11

SRCS := $(wildcard *.c)
EXECS := $(patsubst %.c,%,$(SRCS))

.PHONY: all
all: $(EXECS) Makefile

%: %.c
	$(CC) $^ ../hashtable.a -o ../example_$@ -I ..
