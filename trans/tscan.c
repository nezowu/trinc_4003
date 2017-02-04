#include "tryte.h"
#include <string.h>

int main() {
	Tryte_t min_a = {2, 2, 2, 1}; //53 < a
	Tryte_t max_digit = {0, 0, 0, 2}; //54 > 9
	Tryte_t min_digit = {1, 2, 1, 1}; //43 < 0
	Tryte_t tuff;
	char ch;
	FILE *in;
	in = fopen("prog.bin", "r");
	while(!feof(in)) {
		fread(&tuff, sizeof(Tryte_t), 1, in);
		if(less(tuff, MAX) && less(min_a, tuff)) {
			ch = ternaryToDecimal(tuff) + 43;
		} else if(less(tuff, max_digit) && less(min_digit, tuff)) {
			ch = ternaryToDecimal(tuff) + 4;
		} else
			ch = ternaryToDecimal(tuff);
		printf("%c", ch);
	}
	puts("");
	return 0;
}
