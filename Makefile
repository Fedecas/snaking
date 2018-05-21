ENGINEOBJS = engine/block.c engine/draw.c engine/sound.c engine/window.c
LEVELOBJS = level/food.c level/score.c level/snake.c level/terrain.c level/wall.c
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
PROGRAM = snaking
COMPILER = gcc
SDL = -lSDL2 -lSDL2_ttf -lSDL2_mixer

test: $(ENGINEOBJS) $(LEVELOBJS)
	$(COMPILER) -c $(ENGINEOBJS) $(SDL)
	$(COMPILER) -c $(LEVELOBJS) $(SDL)
	$(COMPILER) -o $(PROGRAM) main.c *.o $(SDL)
	./$(PROGRAM)

clean: 
	rm -f *.o $(PROGRAM)

compile: $(OBJS)
	$(COMPILER) $(CFLAGS) -c $(ENGINEOBJS) $(SDL)
	$(COMPILER) $(CFLAGS) -c $(LEVELOBJS) $(SDL)
	$(COMPILER) $(CFLAGS) main.c *.o $(SDL) -o $(PROGRAM)

