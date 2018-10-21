# Files
EXEC := tardis
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

# Options:
CC := icc
CFLAGS := -I$(TACC_GSL_INC)
LDFLAGS := -L$(TACC_GSL_LIB)
LDLIBS := -lgsl -lgslcblas

# Rules
$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

main.o mytools.o: mytools.h

# Clean
clean:
	rm -f $(OBJ) $(EXEC)
