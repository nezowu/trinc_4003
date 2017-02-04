#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#define N 81
typedef unsigned short T;

typedef struct tryte_t {
	uint8_t ou:2;
	uint8_t one:2;
	uint8_t two:2;
	uint8_t three:2;
} Tryte_t;

Tryte_t BP; 
Tryte_t SP; 
Tryte_t RF; //регистр флагов
Tryte_t MAX = {2, 2, 2, 2}; //80
Tryte_t MIN = {0, 0, 0, 0}; //нул
Tryte_t ONE = {1, 0, 0, 0}; //адын
Tryte_t *Text;
Tryte_t *Data;

typedef struct stack_t {
	        Tryte_t *data;
		Tryte_t *bp;
		Tryte_t *sp;
} Stack_t;

Stack_t Stack;

Tryte_t newT(T ou, T one, T two, T three);
Tryte_t decimalToTernary(T);
T ternaryToDecimal(Tryte_t);
T equal(Tryte_t, Tryte_t);
T less(Tryte_t, Tryte_t);
Tryte_t summ(Tryte_t, Tryte_t);
Tryte_t sub(Tryte_t, Tryte_t);
void push(Tryte_t value);
Tryte_t pop(void);
void initStack(void);
Tryte_t writeBus(Tryte_t *, Tryte_t, Tryte_t); //return nextaddr, bus, addr, data
Tryte_t readBus(Tryte_t *, Tryte_t); //return data, bus, addr
Tryte_t scanStr(void);
int printStr(Tryte_t); //addr

Tryte_t decimalToTernary(T digit) {
	Tryte_t tmp = {0, 0, 0, 0};
	if(digit) {
		tmp.ou = digit % 3;
		if(digit /= 3) {
			tmp.one = digit % 3;
			if(digit /= 3) {
				tmp.two = digit % 3;
				if(digit /= 3)
					tmp.three = digit % 3;
			}
		}
	}
	return tmp;
}

T ternaryToDecimal(Tryte_t st) { //преобразование троичных данных в десятичные
        return st.three*(3*3*3)+st.two*(3*3)+st.one*3+st.ou*1;
}

T equal(Tryte_t dig0, Tryte_t dig1) { // ==
        if(dig0.ou == dig1.ou && dig0.one == dig1.one && dig0.two == dig1.two && dig0.three == dig1.three)
                return 1;
        else
                return 0;
}

T less(Tryte_t dig0, Tryte_t dig1) { // <
        if(dig0.three < dig1.three)
                return 1;
        else if(dig0.three == dig1.three) {
                if(dig0.two < dig1.two)
                        return 1;
                else if(dig0.two == dig1.two) {
                        if(dig0.one < dig1.one)
                                return 1;
                        else if(dig0.one == dig1.one) {
                                if(dig0.ou < dig1.ou)
                                        return 1;
                        }
                }
        }
        return 0;
}

Tryte_t summ(Tryte_t reg0, Tryte_t reg1) { //сумматор двух регистров
        T sum = reg0.ou + reg1.ou;
        switch(sum) {
                case 4:
                        reg0.ou = 1;
                        sum = 1;
                        break;
                case 3:
                        reg0.ou = 0;
                        sum = 1;
                        break;
                case 2:
                        reg0.ou = 2;
                        sum = 0;
                        break;
                case 1:
                        reg0.ou = 1;
                        sum = 0;
                        break;
                case 0:
                        reg0.ou = 0;
                        sum = 0;
                        break;
                default:
                        perror("kernel_panic");
                        exit(EXIT_FAILURE);
        }
        sum += (reg0.one + reg1.one);
        switch(sum) {
                case 5:
                        reg0.one = 2;
                        sum = 1;
                        break;
                case 4:
                        reg0.one = 1;
                        sum = 1;
                        break;
                case 3:
                        reg0.one = 0;
                        sum = 1;
                        break;
                case 2:
                        reg0.one = 2;
                        sum = 0;
                        break;
                case 1:
                        reg0.one = 1;
                        sum = 0;
                        break;
                case 0:
                        reg0.one = 0;
                        sum = 0;
                        break;
                default:
                        perror("kernel_panic");
                        exit(EXIT_FAILURE);
        }
        sum += (reg0.two + reg1.two);
        switch(sum) {
                case 5:
                        reg0.two = 2;
                        sum = 1;
                        break;
                case 4:
                        reg0.two = 1;
                        sum = 1;
                        break;
                case 3:
                        reg0.two = 0;
                        sum = 1;
                        break;
                case 2:
                        reg0.two = 2;
                        sum = 0;
                        break;
                case 1:
                        reg0.two = 1;
                        sum = 0;
                        break;
                case 0:
                        reg0.two = 0;
                        sum = 0;
                        break;
                default:
                        perror("kernel_panic");
                        exit(EXIT_FAILURE);
        }
        sum += (reg0.three + reg1.three);
        switch(sum) {
                case 5:
                        reg0.three = 2;
                        sum = 1;
                        break;
                case 4:
                        reg0.three = 1;
                        sum = 1;
                        break;
                case 3:
                        reg0.three = 0;
                        sum = 1;
                        break;
                case 2:
                        reg0.three = 2;
                        sum = 0;
                        break;
                case 1:
                        reg0.three = 1;
                        sum = 0;
                        break;
                case 0:
                        reg0.three = 0;
                        sum = 0;
                        break;
                default:
                        perror("kernel_panic");
                        exit(EXIT_FAILURE);
        }
        if(sum == 1) {
                RF.ou = sum;
                reg0.ou = reg0.one;
                reg0.one = reg0.two;
                reg0.two = reg0.three;
                reg0.three = sum;
        }
        return reg0;
}

Tryte_t sub(Tryte_t reg0, Tryte_t reg1) { // -
        T sub = 0;
        if(less(reg0, reg1)) {
                Tryte_t temp;
                memcpy(&temp, &reg0, 1);
                memcpy(&reg0, &reg1, 1);
                memcpy(&reg1, &temp, 1);
                RF.one = 1;
        } else
                RF.one = 0;
        if(reg0.ou < reg1.ou) {
                sub = 3;
                reg1.one += 1;
        }
        reg0.ou = reg0.ou + sub - reg1.ou;
        sub = 0;

        if(reg0.one < reg1.one) {
                sub = 3;
                reg1.two += 1;
        }
        reg0.one = reg0.one + sub - reg1.one;
        sub = 0;

        if(reg0.two < reg1.two) {
                sub = 3;
                reg1.three += 1;
        }
        reg0.two = reg0.two + sub - reg1.two;
        sub = 0;

        reg0.three = reg0.three - reg1.three;
        return reg0;
}

void push(Tryte_t value) {
        assert(equal(SP, MAX) != 1);
        *Stack.sp = summ(*Stack.sp, ONE);
        Stack.data = (Tryte_t *)realloc(Stack.data, sizeof(Tryte_t) * ternaryToDecimal(*Stack.sp));
        *(Stack.data + ternaryToDecimal(*Stack.sp) - 1) = value;
}

Tryte_t pop(void) {
        Tryte_t tmp;
        assert(equal(SP, MIN) == 0);
        *Stack.sp = sub(*Stack.sp, ONE);
        tmp = *(Stack.data + ternaryToDecimal(*Stack.sp));
        Stack.data = (Tryte_t *)realloc(Stack.data, sizeof(Tryte_t) * ternaryToDecimal(*Stack.sp));
        return tmp;
}

void initStack(void) {
        Stack.data = malloc(0); //смело присваиваем адресу реальное значение, а не NULL,
        Stack.sp = &SP;         //потому, что при top == 0 невозможжно получить
        *Stack.sp = decimalToTernary(0); //данные по этому адресу с помощью функции pop
        Stack.bp = &BP;
        *Stack.bp = decimalToTernary(0); //newT(0, 0, 0, 0} но так проще
}

Tryte_t writeBus(Tryte_t *bus, Tryte_t addr, Tryte_t data) {
        memcpy((bus + ternaryToDecimal(addr)), &data, sizeof(Tryte_t));
        return summ(addr, ONE);
}

Tryte_t readBus(Tryte_t *bus, Tryte_t addr) {
        Tryte_t tmp = {0, 0, 0, 0};
        memcpy(&tmp, (bus + ternaryToDecimal(addr)), sizeof(Tryte_t));
        return tmp;
}

Tryte_t newT(T ou, T one, T two, T three) { //функция для переопределения переменной
	Tryte_t tmp = {ou, one, two, three};
	return tmp; 
}

Tryte_t scanStr(void) {
        Tryte_t asciiNext = {0, 0, 0, 0}; 
        char buff[N];
        scanf("%80[^\n]%*c", buff);
        size_t count = strlen(buff);
        asciiNext = writeBus(Data, asciiNext, decimalToTernary(count));
        for(T i = 0; i < count; i++) {
                buff[i] = toupper(buff[i]);
                if(buff[i] > 31 && buff[i] < 97) 
                        buff[i] -= 31; //1-65
                else if(122 < buff[i] && buff[i] < 127)
                        buff[i] -= 57; //66-69
                else
                        buff[i] = 1; //неизвестные символы делаем пробельными
                printf("%d\n", buff[i]);
                asciiNext = writeBus(Data, asciiNext, decimalToTernary(buff[i])); 
        }
        return asciiNext; //следующая свободная ячейка
}

int printStr(Tryte_t addr) {
        char ch;
        T size = ternaryToDecimal(readBus(Data, addr));
        addr = summ(addr, ONE);
        for(T i = 1; i <= size; i++) {
                ch = ternaryToDecimal(readBus(Data, addr));
                addr = summ(addr, ONE);
                if(ch < 66 && ch > 0) 
                        ch += 31; 
                else if(ch > 65 && ch < 70)
                        ch += 57; 
                else
                        ch = 63;
                printf("%c", tolower(ch));
        }
        puts("");
        return size;
}
// написать initBus() инициализирующие две памяти, а может зафигачить
// в initStack
// определить флаги в ноль и все регистры
