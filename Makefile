CXX       = g++-8 
CXXFLAGS  = -std=c++17 $(DEBUG)
DEBUG     = -g3 -Wall
LIBS      = `sdl2-config --cflags --libs` -lGLEW -lGL -lSOIL -lboost_system -lboost_filesystem -lSDL2_ttf
OBJS      = $(MAINOBJS) $(CONTOBJS) $(DRAWOBJS) $(COMPOBJS) $(TITLEOBJS) $(_2048OBJS)
PROGRAM   = game

MAINPASS  = main/
COMPPASS  = component/
TITLEPASS = title/
_2048PASS = _2048/

MAINOBJS  = $(MAINPASS)main.o $(MAINPASS)game.o $(MAINPASS)mathematics.o $(MAINPASS)actor.o
CONTOBJS  = $(MAINPASS)input_system.o $(MAINPASS)controller.o $(MAINPASS)renderer.o
DRAWOBJS  = $(MAINPASS)texture.o $(MAINPASS)vertex_array.o $(MAINPASS)shader.o $(MAINPASS)font.o
COMPOBJS  = $(COMPPASS)component.o $(COMPPASS)sprite_component.o $(COMPPASS)texture_component.o $(COMPPASS)rectangle_component.o $(COMPPASS)string_component.o $(COMPPASS)gamepad_component.o $(COMPPASS)move_component.o
TITLEOBJS = $(TITLEPASS)title.o
_2048OBJS = $(_2048PASS)_2048.o $(_2048PASS)setting.o $(_2048PASS)board.o $(_2048PASS)tile.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:; rm -f *.o */*.o *~ $(PROGRAM)

debug:
	#$(CC) -c -o $(MAINPASS)main.o $(MAINPASS)main.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)game.o $(MAINPASS)game.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)mathematics.o $(MAINPASS)mathematics.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)actor.o $(MAINPASS)actor.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)input_system.o $(MAINPASS)input_system.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)controller.o $(MAINPASS)controller.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)renderer.o $(MAINPASS)renderer.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)texture.o $(MAINPASS)texture.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)vertex_array.o $(MAINPASS)vertex_array.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)shader.o $(MAINPASS)shader.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(MAINPASS)font.o $(MAINPASS)font.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(COMPPASS)component.o $(COMPPASS)component.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(COMPPASS)sprite_component.o $(COMPPASS)sprite_component.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(COMPPASS)texture_component.o $(COMPPASS)texture_component.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(COMPPASS)rectangle_component.o $(COMPPASS)rectangle_component.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(COMPPASS)string_component.o $(COMPPASS)string_component.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(COMPPASS)gamepad_component.o $(COMPPASS)gamepad_component.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(COMPPASS)move_component.o $(COMPPASS)move_component.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(TITLEPASS)title.o $(TITLEPASS)title.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(_2048PASS)_2048.o $(_2048PASS)_2048.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(_2048PASS)setting.o $(_2048PASS)setting.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(_2048PASS)board.o $(_2048PASS)board.cpp $(CFLAGS) $(DEBUG)
	#$(CC) -c -o $(_2048PASS)tile.o $(_2048PASS)tile.cpp $(CFLAGS) $(DEBUG)
	#
	#$(CC) $(OBJS) $(LIBS) $(DEBUG) -o $(PROGRAM)
