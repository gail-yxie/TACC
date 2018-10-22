# Files
EXEC := integrate
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,%.o,$(SRC))

# Options:
CC := g++

# Rules
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ 

%.o: %.c
	$(CC) -c $<

main.o func.o: func.h

# Clean
clean:
	rm -f $(OBJ) $(EXEC)
