CXX       = g++-8 
CXXFLAGS  = -std=c++17 $(DEBUG)
DEBUG     = -g3 -Wall
LIBS      = `sdl2-config --cflags --libs` -lGLEW -lGL -lSOIL -lboost_system -lboost_filesystem -lSDL2_ttf
OBJS      = $(MAINOBJS) $(CONTOBJS) $(DRAWOBJS) $(COMPOBJS) $(TITLEOBJS) $(_2048OBJS) $(TETRISOBJS)
PROGRAM   = game

MAINPASS   = main/
COMPPASS   = component/
TITLEPASS  = title/
_2048PASS  = _2048/
TETRISPASS = tetris/

MAINOBJS   = $(MAINPASS)main.o $(MAINPASS)game.o $(MAINPASS)mathematics.o $(MAINPASS)actor.o
CONTOBJS   = $(MAINPASS)input_system.o $(MAINPASS)controller.o $(MAINPASS)renderer.o
DRAWOBJS   = $(MAINPASS)texture.o $(MAINPASS)vertex_array.o $(MAINPASS)shader.o $(MAINPASS)font.o
COMPOBJS   = $(COMPPASS)component.o $(COMPPASS)sprite_component.o $(COMPPASS)texture_component.o $(COMPPASS)rectangle_component.o $(COMPPASS)string_component.o $(COMPPASS)gamepad_component.o $(COMPPASS)move_component.o
TITLEOBJS  = $(TITLEPASS)title.o
_2048OBJS  = $(_2048PASS)_2048.o $(_2048PASS)setting.o $(_2048PASS)board.o $(_2048PASS)tile.o
TETRISOBJS = $(TETRISPASS)tetris.o $(TETRISPASS)title.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(OBJS) $(LIBS) -o $(PROGRAM)

clean:; rm -f *.o */*.o *~ $(PROGRAM)

tetris_clean:; rm -f $(TETRISPASS)*.o $(MAINPASS)controller.o $(PROGRAM)