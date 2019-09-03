
CC            = g++
CFLAGS        = -g3 -Wall
LIBS          = `sdl2-config --cflags --libs` -lGLEW -lGL -lSOIL -lboost_system -lboost_filesystem -lSDL2_ttf
OBJS          = $(MAINOBJS)
MAINOBJS      = main/main.o
PROGRAM       = game

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:; rm -f *.o */*.o *~ $(PROGRAM)

debug:
	$(CC) main/main.cpp $(CFLAGS) $(LIBS) -o $(PROGRAM)