#include "tryte.h"

void hexd(uint8_t);

int main(void) {
	Tryte_t d = {0, 0, 0, 0};
	for(int i = 0; i < N; i++) {
		printf("%d %d%d%d%d\t", ternaryToDecimal(d), d.three, d.two, d.one, d.ou);
		hexd(d.three), hexd(d.two), hexd(d.one), hexd(d.ou);
		puts("");
		d = summ(d, ONE);
	}
	printf("%d\n", atoi("1b3"));
	return 0;
}
void hexd(uint8_t dig) {
	switch(dig) {
		case 0: printf("%s", "00");
			break;
		case 1: printf("%s", "01");
			break;
		case 2: printf("%s", "10");
	}
}
