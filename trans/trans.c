#include "tryte.h"
#include <string.h>

int main() {
	T size;
	T i = 0;
	Tryte_t tuff[80];
	char ch;
	FILE *in;
	FILE *out;
	in = fopen("prog.t", "r");
	out = fopen("prog.bin", "w");
	while(!feof(in)) {
		fread(&ch, sizeof(Tryte_t), 1, in);
		if(ch < 123 && ch > 96) {
			ch = ch - 43;
			tuff[i] = decimalToTernary(ch);
		} else if(ch < 58 && ch > 47) {
			ch = ch - 4;
			tuff[i] = decimalToTernary(ch);
		} else
			tuff[i] = decimalToTernary(32);
		i++;
	}
	size = ftell(in) -1;
	printf("%d\n", size);
	fwrite(tuff, sizeof(Tryte_t), size, out);
	return 0;
}
