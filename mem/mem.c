#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define N 82

typedef struct tryte_t {
	uint8_t three:2;
	uint8_t two:2;
	uint8_t one:2;
	uint8_t ou:2;
} Tryte_t;

Tryte_t *addr;
Tryte_t data;
unsigned short ternary_to_decimal(Tryte_t *);
Tryte_t decimal_to_ternary(unsigned short);


//Tryte_t ram(Tryte_t);
//
//Tryte_t ram(Tryte_t addr, ...) {
//	Tryte_t *addr = malloc(N);
//	if(control == 0) { // чтение из памяти
//		return *(addr + 
int main(void) {
	unsigned short chislo = 90; //лимит 80
	unsigned short esheodno = 27;
	int mem = 0;
	Tryte_t test = {0, 2, 1, 0}; //21
	Tryte_t tost = {0, 1, 2, 2}; //17
	Tryte_t tist = {0, 0, 1, 2}; //5
	addr = (Tryte_t *)malloc(N);
	memcpy((addr + mem), &test, 1);
	mem++;
	memcpy((addr + mem), &tost, 1);
	mem++;
	memcpy((addr + mem), &tist, 1);
	mem++;
	memcpy((addr + mem), &test, 1);
	mem++;
	Tryte_t tust = decimal_to_ternary(chislo);
	memcpy((addr + mem), &tust, 1);
	tust = decimal_to_ternary(esheodno);
	mem++;
	memcpy((addr + mem), &tust, 1);
	for(int i = 0; i < N; i++)
//		printf("%d %p\n", (addr+i)->three*(3*3*3)+(addr+i)->two*(3*3)+(addr+i)->one*3+(addr+i)->ou*1, (addr+i)); // *(addr+i), (addr+i)
		printf("%hu %p\n", ternary_to_decimal(addr+i), (addr+i));
	return 0;
}

unsigned short ternary_to_decimal(Tryte_t *st) {
	return st->three*(3*3*3)+st->two*(3*3)+st->one*3+st->ou*1;
}

Tryte_t decimal_to_ternary(unsigned short digit) {
	Tryte_t temp;
	temp.ou = digit % 3;
	if(digit /= 3) {
		temp.one = digit % 3;
		if(digit /= 3) {
			temp.two = digit % 3;
			if(digit /= 3)
				temp.three = digit % 3;
		}
	}
	return temp;
}
