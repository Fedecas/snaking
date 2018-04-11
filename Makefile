OBJS = window.c draw.c snake.c food.c block.c terrain.c wall.c
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
PROGRAM = snaking
COMPILER = gcc
SDL = -lSDL2 -lSDL2_ttf

test: $(OBJS)
	$(COMPILER) -c $(OBJS) $(SDL)
	$(COMPILER) main.c *.o $(SDL) -o $(PROGRAM)
	./$(PROGRAM)

clean: 
	rm -f *.o snake

compile: $(OBJS)
	$(COMPILER) $(CFLAGS) -c $(OBJS) $(SDL)
	$(COMPILER) $(CFLAGS) main.c *.o $(SDL) -o $(PROGRAM)
