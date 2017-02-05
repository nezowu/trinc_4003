#include "tryte.h"

char asciiToOscii(char ch) {
	ch = toupper(ch);
	if(ch > 31 && ch < 97) 
		ch -= 31; //1-65
	else if(122 < ch && ch < 128)
		ch -= 57; //66-70
	else
		ch = 1; //неизвестные символы делаем пробельными
	return ch;
}

char osciiToAscii(char ch) {
	if(ch < 66 && ch > 0)  
		ch += 31; 
	else if(ch > 65 && ch < 71) 
		ch += 57; 
	else
		ch = 63; //неизвестным символам присвоим знак вопроса
	return tolower(ch);
}

int main(int argc, char *argv[]) {
	Data = (Tryte_t *)malloc(N);
	Tryte_t addr = {0, 0, 0, 0};
	char ch;
	int count = 0;
	FILE *in, *out;
	in = fopen("in.txt", "r");
	assert(in);
	out = fopen("out.bin", "w");
	assert(out);
	Tryte_t tmp;

	while(fread(&ch, sizeof(char), 1, in)) {
		ch = asciiToOscii(ch); //osciiToascii()
		tmp = decimalToTernary(ch);
		addr = writeBus(Data, addr, tmp);
		if(count == 3)
			addr = writeBus(Data, addr, MAX);
		count++;
	}

	fclose(in);

	fwrite(Data, sizeof(Tryte_t), 10, out);

	fclose(out);
	out = fopen("out.bin", "r");
	assert(out);
	while(fread(&tmp, sizeof(Tryte_t), 1, out)) {
		ch = ternaryToDecimal(tmp);
		ch = osciiToAscii(ch);
		printf("%c", ch);
	}
	puts("");
	return EXIT_SUCCESS;
}
