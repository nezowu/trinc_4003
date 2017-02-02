#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned short T;

typedef struct tryte_t {
	uint8_t ou:2, one:2, two:2, three:2;
} Tryte_t;

Tryte_t r0;
Tryte_t r1;
Tryte_t r2;
Tryte_t r3;
Tryte_t rf; // регистр флагов

int main(int argc, char *argv[]) {
	r0.three = 0, r0.two = 0, r0.one = 0, r0.ou = 0;
	r1.three = 0, r1.two = 0, r1.one = 0, r1.ou = 1;
	r2.three = 0, r2.two = 2, r2.one = 2, r2.ou = 2;
	r3.three = 0, r3.two = 1, r3.one = 1, r3.ou = 2;
	rf.three = 0, rf.two = 0, rf.one = 0, rf.ou = 0; // регистр флагов

	printf("%d%d%d%de%d\n", r0.three, r0.two, r0.one, r0.ou, rf.ou);
	// загружаем двоичную программу в память.
//	FILE *prog;
//	prog = fopen(argv[1], "r");
//	if(!prog) {
//		perror("can't open programm file");
//		return(1);
//	}
//	fwrite(&mem, sizeof(mem), 1, prog);
//	printf("%d %d %d %d\n", mem.ou, mem.one, mem.two, mem.three);
	return 0;
}
