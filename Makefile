CC            = g++-8
CFLAGS        = -g3 -Wall
LIBS          = `sdl2-config --cflags --libs` -lGLEW -lGL -lSOIL -lboost_system -lboost_filesystem -lSDL2_ttf
OBJS          = $(MAINOBJS) $(COMPONENTOBJS) $(_2048OBJS)
MAINOBJS      = main/main.o main/game.o main/input_system.o main/mathematics.o main/renderer.o main/actor.o main/controller.o main/texture.o main/vertex_array.o main/shader.o
COMPONENTOBJS = component/component.o component/sprite_component.o
_2048OBJS     = _2048/_2048.o _2048/tile.o
PROGRAM       = game

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:; rm -f *.o */*.o *~ $(PROGRAM)

debug:
	$(CC) main/main.cpp main/game.cpp main/input_system.cpp main/mathematics.cpp main/renderer.cpp main/actor.cpp main/controller.cpp main/texture.cpp main/shader.cpp main/vertex_array.cpp component/component.cpp component/sprite_component.cpp _2048/_2048.cpp _2048/tile.cpp $(CFLAGS) $(LIBS) -o $(PROGRAM)
