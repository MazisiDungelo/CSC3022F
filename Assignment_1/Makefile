./# This is a Makefile comment

# Declare some variables to help construct our compile command
CC=g++         # the compiler
LIBS=-lm       # the libraries we will ref

# Need object files Fib.o and FibDriver.o to create exe fibonacci 
myWordCount: myWC.o myWCdriver.o
	$(CC) myWC.o myWCdriver.o -o myWordCount $(LIBS)

# Need Fib.cpp and Fib.h to create object file Fib.o 
myWC.o: myWC.cpp myWC.h
	$(CC) -c myWC.cpp

# Need FibDriver.cpp to create object file FibDriver.o
myWCdriver.o: myWCdriver.cpp
	$(CC) -c myWCdriver.cpp
   
# other rules; invoked by make clean etc 

# deletes all the object code files
clean:
	@rm -f *.o
	@rm myWordCount
   
# copies/moves the relevant binaries and/or libraries to the correct folders   
install:
  
	@mv myWordCount ~/bin
