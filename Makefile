CC            = g++
CFLAGS        = -g3 -Wall
LIBS          = `sdl2-config --cflags --libs` -lGLEW -lGL -lSOIL -lboost_system -lboost_filesystem -lSDL2_ttf
OBJS          = $(MAINOBJS)
MAINOBJS      = main/main.o main/game.o main/input_system.o main/mathematics.o main/renderer.o main/controller.o
PROGRAM       = game

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:; rm -f *.o */*.o *~ $(PROGRAM)

debug:
	$(CC) main/main.cpp main/game.cpp main/input_system.cpp main/mathematics.cpp main/renderer.cpp main/controller.cpp  $(CFLAGS) $(LIBS) -o $(PROGRAM)