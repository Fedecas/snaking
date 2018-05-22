ENGINEOBJS = engine/block.c engine/draw.c engine/sound.c engine/window.c
LEVELOBJS = level/food.c level/score.c level/snake.c level/terrain.c level/wall.c
OBJS = button.c handlers.c
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
PROGRAM = snaking
COMPILER = gcc
SDL = -lSDL2 -lSDL2_ttf -lSDL2_mixer

test: $(ENGINEOBJS) $(LEVELOBJS) $(OBJS)
	$(COMPILER) -c $(ENGINEOBJS) $(SDL)
	$(COMPILER) -c $(LEVELOBJS) $(SDL)
	$(COMPILER) -c $(OBJS) $(SDL)
	$(COMPILER) -o $(PROGRAM) main.c *.o $(SDL)
	./$(PROGRAM)

clean: 
	rm -f *.o $(PROGRAM)

compile: $(ENGINEOBJS) $(LEVELOBJS) $(OBJS)
	$(COMPILER) $(CFLAGS) -c $(ENGINEOBJS) $(SDL)
	$(COMPILER) $(CFLAGS) -c $(LEVELOBJS) $(SDL)
	$(COMPILER) $(CFLAGS) -c $(OBJS) $(SDL)
	$(COMPILER) $(CFLAGS) -o $(PROGRAM) main.c *.o $(SDL) 

