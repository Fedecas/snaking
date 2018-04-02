OBJS = window.c draw.c color.c
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99
PROGRAM = snake
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
