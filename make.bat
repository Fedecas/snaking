gcc -c engine/block.c engine/button.c engine/draw.c engine/font.c engine/handlers.c engine/sound.c engine/window.c -IC:\MinGW\include\SDL2 -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer
gcc -c level/food.c level/score.c level/snake.c level/terrain.c level/wall.c -w
gcc -o snaking main.c *.o -IC:\MinGW\include\SDL2 -LC:\MinGW\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer
