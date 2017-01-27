#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct tryte_t {
	uint8_t one:2;
	uint8_t two:2;
	uint8_t three:2;
	uint8_t four:2;
} Tryte_t;

int main(void) {
	Tryte_t test = {3, 2, 1, 0};
	Tryte_t tost = {0, 1, 2, 3};
	Tryte_t tist = {0, 0, 0, 0};
	char **addr = malloc(sizeof(char *) * 82);
	for(int i = 0; i < 82; i++)
		addr[i] = malloc(sizeof(char));
	memcpy(addr[0], &test, 1);
	memcpy(addr[1], &tost, 1);
	memcpy(addr[2], &tist, 1);
	memcpy(addr[3], &test, 1);
	printf("%d %p\n", *addr[0], addr[0]);
	printf("%d %p\n", *addr[1], addr[1]);
	printf("%d %p\n", *addr[2], addr[2]);
	printf("%d %p\n", *addr[3], addr[3]);
	return 0;
}
