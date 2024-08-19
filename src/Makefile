CC=gcc -std=gnu17 -Wall -Wextra -MMD

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)

bin2array: $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $<

clean:
	/bin/rm -f $(OBJS) $(DEPS) bin2array

-include $(DEPS)
