CFLAGS=-Wall -O2
LDFLAG=
cpu: cpu.o
	cc $(CFLAGS) cpu.o -o cpu
cpu.o: cpu.c
	cc -c $(CFLAGS) cpu.c
clean:
	find . -maxdepth 2 -type f \( -perm /u+x -o -name "*.o" \) -delete
