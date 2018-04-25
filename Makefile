OBJS = block.c draw.c food.c score.c snake.c terrain.c wall.c window.c
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
PROGRAM = snaking
COMPILER = gcc
SDL = -lSDL2 -lSDL2_ttf

test: $(OBJS)
	$(COMPILER) -c $(OBJS) $(SDL)
	$(COMPILER) -o $(PROGRAM) main.c *.o $(SDL)
	./$(PROGRAM)

clean: 
	rm -f *.o snake

compile: $(OBJS)
	$(COMPILER) $(CFLAGS) -c $(OBJS) $(SDL)
	$(COMPILER) $(CFLAGS) main.c *.o $(SDL) -o $(PROGRAM)
