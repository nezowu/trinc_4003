#include "tryte.h"
#include <stdio.h>
#include <ctype.h>

int main(void) {
	Tryte_t d = {0, 0, 0, 0};
	int dig;
	Tryte_t tmp;
	for(int i = 0; i < N; i++) {
		printf("%hu %hu\n", (T)ternaryToDecimal(d), (T)ternaryToDecimal(tmp = decimalToTernary(dig = (T)ternaryToDecimal(d))));
		d = summ(d, ONE);
	}
	return 0;
}
