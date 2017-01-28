CFLAGS=-Wall -O2
LDFLAG=
launch: main.o
	cc $(CFLAGS) main.o -o launch
main.o: main.c
	cc -c $(CFLAGS) main.c
clean:
	find . -maxdepth 2 -type f \( -perm /u+x -o -name "*.o" \) -delete
