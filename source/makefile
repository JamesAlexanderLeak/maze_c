OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -std=c99 -g

all : amaze

test : amaze
	./amaze -v

valgrind : amaze
	valgrind amaze -r 2777 -c 16 16 unready.maze -d ready.maze -s unready.maze ready.maze

clean : 
	rm -f $(OBJS) amaze

amaze : $(OBJS)
	gcc $(LOPTS) da.c cda.c queue.c stack.c cell.c maze.c main.c -o amaze
