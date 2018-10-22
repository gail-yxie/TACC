# Files
EXEC := integrate
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))

# Options:
CC := g++

# Rules
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ 

%.o: %.cpp %.h
	$(CC) -c $<

main.o simpson.o trapezoid.o fx.o: fx.h

# Clean
clean:
	rm -f $(OBJ) $(EXEC)
