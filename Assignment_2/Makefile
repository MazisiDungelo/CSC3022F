# This is a Makefile comment
# Declare some variables to help construct our compile command
CC=g++         # the compiler
LIBS=-lm       # the libraries we will ref

# Need object files Tile, TileManager.o and driver.o to create exe Puzzle
Puzzle: Tile.o TileManager.o driver.o
	$(CC) Tile.o TileManager.o driver.o -o Puzzle $(LIBS)

# Need Tile and Tile.h to create object file Tile.o 
Tile.o: Tile.cpp Tile.h
	$(CC) -c Tile.cpp

# Need TileManager.cpp to create object file TileManager.o
TileManager.o: TileManager.cpp TileManager.h
	$(CC) -c TileManager.cpp

# Need Tile and Tile.h to create object file Tile.o 
driver.o: driver.cpp
	$(CC) -c driver.cpp

# deletes all the object code files
clean:
	rm -f *.o
	rm Puzzle
   
# copies/moves the relevant binaries and/or libraries to the correct folders   
install:
  
	mv Puzzle ~/bin