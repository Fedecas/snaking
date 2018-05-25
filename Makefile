COMPILER = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
PROGRAM = snaking
SDL = -lSDL2 -lSDL2_ttf -lSDL2_mixer

ENGINEOBJS = engine/block.c engine/button.c engine/draw.c engine/font.c engine/handlers.c engine/sound.c engine/window.c
LEVELOBJS = level/food.c level/score.c level/snake.c level/terrain.c level/wall.c

all: test

compile_engine:
	$(COMPILER) $(CCFLAGS) -c $(ENGINEOBJS) $(SDL)

compile_level: compile_engine
	$(COMPILER) $(CCFLAGS) -c $(LEVELOBJS) $(SDL)

compile: compile_level
	$(COMPILER) -o $(PROGRAM) main.c *.o $(SDL)

test: compile
	./$(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)

valgrind: compile
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROGRAM)
