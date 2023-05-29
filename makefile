all: manager talker clean

manager: manager.o
	gcc -o manager manager.o -pthread

manager.o: manager.c funciones_manager.h
	gcc -c manager.c

talker: talker.o
	gcc -o talker talker.o -pthread

talker.o: talker.c funciones_talker.h
	gcc -c talker.c

clean:
	rm -f *.o
