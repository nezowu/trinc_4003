#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* определим структуру минимального блока памяти
 * с которым оперирует этот процессор размером в 1 байт == 1 трайт
 * один бит не используется, единица адресации 1 трайт.
 * спецификацию напишу позже; */

typedef struct tryte_t {
	uint8_t one:2, two:2, three:2, four:2;
} Tryte_t;

Tryte_t summ(Tryte_t, Tryte_t, Tryte_t *);

int main(int argc, char *argv[]) {
//	Tryte_t *mem;
	Tryte_t r0 = {2, 2, 2, 2};
	Tryte_t r1 = {2, 2, 2, 2};
	Tryte_t rf = {0, 0, 0, 0}; // регистр флагов

	r0 = summ(r0, r1, &rf);
	printf("%d%d%d%d\n", r0.four, r0.three, r0.two, r0.one);
	printf("%d\n", rf.one);

	// выделяем доступную память примерно 13Кб;
	// нет пока разделения между секциями;
//	mem = (Tryte *)malloc(sizeof(Tryte) + 1);
	// определяем регистры;
//	Tryte r0;
//	Tryte r1;
//	Tryte r2;
	// загружаем двоичную программу в память.
//	FILE *prog;
//	prog = fopen(argv[1], "r");
//	if(!prog) {
//		perror("can't open programm file");
//		return(1);
//	}
//	fwrite(&mem, sizeof(mem), 1, prog);
//	printf("%d %d %d %d\n", mem.one, mem.two, mem.three, mem.four);
	return 0;
}


Tryte_t summ(Tryte_t reg0, Tryte_t reg1, Tryte_t *flag) { //сумматор двух регистров
	int sum = reg0.one + reg1.one;
	switch(sum) {
		case 4:
			reg0.one = 1;
			sum = 1;
			break;
		case 3:
			reg0.one = 0;
			sum = 1;
			break;
		case 2:
			reg0.one = 2;
			sum = 0;
			break;
		case 1:
			reg0.one = 1;
			sum = 0;
			break;
		case 0:
			reg0.one = 0;
			sum = 0;
			break;
		default:
			perror("kernel_panic");
			exit(EXIT_FAILURE);
	}
	sum += (reg0.two + reg1.two);
	switch(sum) {
		case 5:
			reg0.two = 2;
			sum = 1;
			break;
		case 4:
			reg0.two = 1;
			sum = 1;
			break;
		case 3:
			reg0.two = 0;
			sum = 1;
			break;
		case 2:
			reg0.two = 2;
			sum = 0;
			break;
		case 1:
			reg0.two = 1;
			sum = 0;
			break;
		case 0:
			reg0.two = 0;
			sum = 0;
			break;
		default:
			perror("kernel_panic");
			exit(EXIT_FAILURE);
	}
	sum += (reg0.three + reg1.three);
	switch(sum) {
		case 5:
			reg0.three = 2;
			sum = 1;
			break;
		case 4:
			reg0.three = 1;
			sum = 1;
			break;
		case 3:
			reg0.three = 0;
			sum = 1;
			break;
		case 2:
			reg0.three = 2;
			sum = 0;
			break;
		case 1:
			reg0.three = 1;
			sum = 0;
			break;
		case 0:
			reg0.three = 0;
			sum = 0;
			break;
		default:
			perror("kernel_panic");
			exit(EXIT_FAILURE);
	}
	sum += (reg0.four + reg1.four);
	switch(sum) {
		case 5:
			reg0.four = 2;
			sum = 1;
			break;
		case 4:
			reg0.four = 1;
			sum = 1;
			break;
		case 3:
			reg0.four = 0;
			sum = 1;
			break;
		case 2:
			reg0.four = 2;
			sum = 0;
			break;
		case 1:
			reg0.four = 1;
			sum = 0;
			break;
		case 0:
			reg0.four = 0;
			sum = 0;
			break;
		default:
			perror("kernel_panic");
			exit(EXIT_FAILURE);
	}
//	printf("%d%d%d%d\n", reg0.four, reg0.three, reg0.two, reg0.one);
	if(sum == 1) {
		flag->one = sum;
		reg0.one = reg0.two;
		reg0.two = reg0.three;
		reg0.three = reg0.four;
		reg0.four = sum;
	}
	return reg0;
}
