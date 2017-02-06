#include "tryte.h"

char asciiToOscii(char);
char osciiToAscii(char);
void upStart(char *);

int main(int argc, char *argv[]) {
	char ch;
	Data = (Tryte_t *)malloc(N);
	Text = (Tryte_t *)malloc(N);
	Tryte_t temp;
	Tryte_t addr_Text = {0, 0, 0, 0};
	Tryte_t addr_Data = {0, 0, 0, 0};

	if(argc == 2) {
		upStart(argv[1]);

		addr_Text = newT(0, 0, 0, 0);
		while(!equal(temp, MAX)) {
			temp = readBus(Text, addr_Text);
			ch = ternaryToDecimal(temp);
			ch = osciiToAscii(ch);
			printf("%c", ch);
			addr_Text = summ(addr_Text, ONE);
		}
		puts("");
		addr_Data = newT(0, 0, 0, 0);
		while(!equal(temp, MIN)) {
			temp = readBus(Data, addr_Data);
			ch = ternaryToDecimal(temp);
			ch = osciiToAscii(ch);
			printf("%c", ch);
			addr_Data = summ(addr_Data, ONE);
		}
		puts("");
	}
	return EXIT_SUCCESS;
}

void upStart(char *fname) {
	Tryte_t date;
	Tryte_t addr = MIN;
	FILE  *in;
	in = fopen(fname, "r");
	assert(in);
	while(fread(&date, sizeof(Tryte_t), 1, in)) {
		addr = writeBus(Text, addr, date);
		puts("Text ok");
		if(equal(date, MAX))
			break;
	}
	addr = MIN;
	while(fread(&date, sizeof(Tryte_t), 1, in)) {
		addr = writeBus(Data, addr, date);
		puts("Data ok");
	}
}


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

