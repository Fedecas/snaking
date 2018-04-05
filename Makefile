OBJS = window.c draw.c color.c snake.c food.c block.c
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
PROGRAM = snaking
COMPILER = gcc
SDL = -lSDL2

test: $(OBJS)
	$(COMPILER) -c $(OBJS) $(SDL)
	$(COMPILER) -o $(PROGRAM) *.o main.c $(SDL)
	./$(PROGRAM)

clean: 
	rm -f *.o snake

compile: $(OBJS)
	$(COMPILER) $(CFLAGS) -c $(OBJS) $(SDL)
	$(COMPILER) $(CFLAGS) -o $(PROGRAM) *.o main.c $(SDL)
