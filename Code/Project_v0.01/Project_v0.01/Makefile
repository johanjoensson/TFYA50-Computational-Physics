CC = g++

LDFLAGS = -lm

EXE = program

OBJECTS = 	main.o\
		atom.o\
		vector_lib.o\
		verlet_list.o\
		world.o\
		velocity_verlet_integration.o\

all : $(EXE)

%.o : %.c
	$(CC) -o $@ -c $^

program : $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

clean :
	rm $(OBJECTS) $(EXE)
