CC = g++

LDFLAGS = -lm -g -Wall -Wextra -w

EXE = program

OBJECTS = 	main.o\
		atom.o\
		vector_lib.o\
		verlet_list.o\
		world.o\
		velocity_verlet_integration.o\

all : $(EXE)

%.o : %.cpp
	$(CC) -o $@ $(LDFLAGS) -c $^

program : $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

clean :
	rm $(OBJECTS) $(EXE)
