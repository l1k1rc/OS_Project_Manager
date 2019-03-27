all: cmd
commandInterface.o : commandInterface.c command.func.h
	gcc -c commandInterface.c
commmand.func.o : command.func.c
	gcc -c command.func.c
cmd : commandInterface.o command.func.o
	gcc commandInterface.o command.func.o -o cmd
clean:
	rm -f *.o cmd

