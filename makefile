CC=gcc

IDIR=include
ODIR=obj

# define the search path
vpath %.c src
vpath %.h include

# if these get changed it recompiles automaticaly
# files that the program depends on ?
_DEPS = defs.h structs.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# An object file is the real output from the compilation phase. 
# It's mostly machine code, but has info that allows a linker to see what symbols are in it as well as symbols it requires in order to work.
# (For reference, "symbols" are basically names of global objects, functions, etc.)

_OBJ = main.o draw.o init.o input.o stage.o util.o sound.o text.o title.o background.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# flags to give the compiles
LDFLAGS = `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf

CFLAGS = -I$(IDIR)

# this says that all files that end with .o depend on the .c version of the file and the .h files 
# to generate these of files created a dir then compile with gcc 
# -c is used so that the compiler generates the .o file
#  -o $@ says to put the output of the compilation in the file named on the left side of the : so game in this case
#  and $< is first item in dependencies list

$(ODIR)/%.o: %.c %.h $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

#$(ODIR)/%.o: %.c %.h $(DEPS)
#	$(CC) -c -o $@ $< #$(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

