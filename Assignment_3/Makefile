# This is a Makefile comment
# Declare some variables to help construct our compile command
CC=g++         # the compiler
LIBS=-lm       # the libraries we will ref

# Need object files ConnectedComponent.o, PGMimageProcessor.o and driver.o to create exe ImageProcessor
ImageProcessor: ConnectedComponent.o PGMimageProcessor.o driver.o
	$(CC) ConnectedComponent.o PGMimageProcessor.o driver.o -o ImageProcessor $(LIBS)

# Need ConnectedComponent.cpp and ConnectedCompoenent.h to create object file ConnectedComponent.o
ConnectedComponent.o: ConnectedComponent.cpp ConnectedComponent.h 
	$(CC) -c ConnectedComponent.cpp

# Need PGMimageProcessor.cpp and PGMimageProcessor.h to create object file PGMimageProcessor.o
PGMimageProcessor.o: PGMimageProcessor.cpp PGMimageProcessor.h
	$(CC) -c PGMimageProcessor.cpp

# Need driver.cpp to create object file driver.o
driver.o: driver.cpp
	$(CC) -c driver.cpp

# deletes all the object code files
clean:
	rm -f *.o
	rm ImageProcessor