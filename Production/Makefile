CFLAGS=-Wall -O2
LDFLAG=
launch: cpu.o
	cc $(CFLAGS) cpu.o -o launch
cpu.o: cpu.c
	cc -c $(CFLAGS) cpu.c
clean:
	find . -maxdepth 1 -type f \( -perm /u+x -o -name "*.o" \) -delete
