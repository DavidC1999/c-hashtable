CFLAGS=-W -Wall -Wextra -Werror -g -std=c11

SRCS := $(wildcard *.c)
EXECS := $(patsubst %.c,%,$(SRCS))

.PHONY: all
all: $(EXECS) Makefile
	for exec in $(EXECS); do \
		mv $$exec ../example_$$exec ; \
	done

%: %.c
	$(CC) $^ ../hashtable.a -o $@ -I ..
