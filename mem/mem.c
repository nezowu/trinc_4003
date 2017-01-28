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
unsigned short ternary_to_decimal(Tryte_t *);
Tryte_t decimal_to_ternary(unsigned short);
Tryte_t ram(Tryte_t, Tryte_t, unsigned short);


int main(void) {
	addr = (Tryte_t *)malloc(N);
	unsigned short chislo = 90; //лимит 80
	unsigned short esheodno = 27;
	int mem = 0;
	Tryte_t test = {0, 2, 1, 0}; //21
	Tryte_t tost = {0, 1, 2, 2}; //17
	Tryte_t tist = {0, 0, 1, 2}; //5
	Tryte_t pervy = {0, 2, 1, 1}; //адрес для записи 22
	Tryte_t data = {1, 2, 2, 0}; //данные для записи 51
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
	ram(pervy, data, 1); //записываем данные по адресу
	for(int i = 0; i < N; i++)
		printf("%hu %p\n", ternary_to_decimal(addr+i), (addr+i));
	data = ram(pervy, data, 0); //считываем данные по адресу
	printf(" Наш выход: %hu\n", ternary_to_decimal(&data));
	return 0;
}

unsigned short ternary_to_decimal(Tryte_t *st) { //преобразование троичных данных в десятичные
	return st->three*(3*3*3)+st->two*(3*3)+st->one*3+st->ou*1;
}

Tryte_t decimal_to_ternary(unsigned short digit) { //преобразование десятичных данных в троичные
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

Tryte_t ram(Tryte_t address, Tryte_t data, unsigned short control) { //функция для записи и чтения
	if(control == 0) { // чтение из памяти
		memcpy(&data, (addr + ternary_to_decimal(&address)), 1);
		return data;
	}
	else {
		memcpy((addr + ternary_to_decimal(&address)), &data, 1);
		return data;
	}
}
