#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define N 81
typedef unsigned short T;

typedef struct tryte_t {
	uint8_t ou:2;
	uint8_t one:2;
	uint8_t two:2;
	uint8_t three:2;
} Tryte_t;

Tryte_t *Text;
Tryte_t *Data;
T ternary_to_decimal(Tryte_t *);
Tryte_t decimal_to_ternary(T);
Tryte_t ram(Tryte_t, Tryte_t, T);
T writeT(Tryte_t *, Tryte_t, Tryte_t);
Tryte_t readT(Tryte_t *, Tryte_t, Tryte_t);
int main(void) {
	Text = (Tryte_t *)malloc(N);
	Data = (Tryte_t *)malloc(N);
	T chislo = 90; //лимит 80
	T esheodno = 27;
	T mem = 0;
	Tryte_t test = {0, 2, 1, 0}; //15
	Tryte_t tost = {0, 1, 2, 2}; //75
	Tryte_t tist = {0, 0, 1, 2}; //63
	Tryte_t pervy = {0, 2, 1, 1}; //адрес для записи 42 (0-80)
	Tryte_t data = {1, 2, 2, 0}; //данные для записи 25
	Tryte_t MAX = {2, 2, 2, 2};
	Tryte_t date = {0, 0, 0, 0};
	memcpy((Text + mem), &test, 1);
	mem++;
	memcpy((Text + mem), &tost, 1);
	mem++;
	memcpy((Text + mem), &tist, 1);
	mem++;
	memcpy((Text + mem), &test, 1);
	mem++;
	Tryte_t tust = decimal_to_ternary(chislo);
	memcpy((Text + mem), &tust, 1);
	tust = decimal_to_ternary(esheodno);
	mem++;
	memcpy((Text + mem), &tust, 1);
	ram(pervy, data, 1); //записываем данные по адресу
	for(int i = 0; i < N; i++)
		printf("%hu %p\n", ternary_to_decimal(Text+i), (Text+i));
	data = ram(pervy, data, 0); //считываем данные по адресу
	printf(" Наш выход: %hu\n", ternary_to_decimal(&data));
	printf("MAX %d\n", ternary_to_decimal(&MAX));
	writeT(Data, pervy, data);
	date = readT(Data, pervy, date);
	printf("%d\n", ternary_to_decimal(&date));
//	for(int j = 0; j < N; j++)
//		printf("%hu %p\n", ternary_to_decimal(Data+j), (Data+j));
	return 0;
}

T ternary_to_decimal(Tryte_t *st) { //преобразование троичных данных в десятичные
	return st->three*(3*3*3)+st->two*(3*3)+st->one*3+st->ou*1;
}

Tryte_t decimal_to_ternary(T digit) { //преобразование десятичных данных в троичные
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

Tryte_t ram(Tryte_t addr, Tryte_t data, T control) { //функция для записи и чтения
	if(control == 0) { // чтение из памяти
		memcpy(&data, (Text + ternary_to_decimal(&addr)), 1);
		return data;
	}
	else {
		memcpy((Text + ternary_to_decimal(&addr)), &data, 1);
		return data;
	}
}

T writeT(Tryte_t *bus, Tryte_t addr, Tryte_t data) { //функция для записи в шину bus
	memcpy((bus + ternary_to_decimal(&addr)), &data, 1);
	return 0;
}

Tryte_t readT(Tryte_t *bus, Tryte_t addr, Tryte_t data) { //функция для чтения из шины bus
	memcpy(&data, (bus + ternary_to_decimal(&addr)), 1);
	return data;
}
