SRC=$(wildcard src/*.c)
OBJS=$(addprefix obj/, $(SRC:.c=.o))

CC=gcc
CFLAGS=-std=gnu17 -ggdb -Wall -Werror

all:
	mkdir -p obj/src
	$(MAKE) calc

calc: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

obj/src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm calc

