#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
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

Tryte_t decimalToTernary(T);
T ternaryToDecimal(Tryte_t);
T equal(Tryte_t, Tryte_t);
T less(Tryte_t, Tryte_t);
Tryte_t summ(Tryte_t, Tryte_t);
Tryte_t sub(Tryte_t, Tryte_t);
void push(Tryte_t value);
Tryte_t pop(void);
void initStack(void);
T writeBus(Tryte_t *, Tryte_t, Tryte_t);
Tryte_t readBus(Tryte_t *, Tryte_t);

int main(void) {
	Text = (Tryte_t *)malloc(N);
	Data = (Tryte_t *)malloc(N);
	initStack();
	puts("Запишем в стек 5, 6, 7, 8");
	Tryte_t value = decimalToTernary(5);
	push(value); //5
	value = summ(value, ONE);
	push(value); //6
	value = summ(value, ONE);
	push(value); //7
	push(summ(value, ONE)); //8
	puts("Снимем последние три значения и выведем на монитор");
	printf("%d\n", ternaryToDecimal(pop()));
	printf("%d\n", ternaryToDecimal(pop()));
	printf("%d\n", ternaryToDecimal(pop()));
	puts("Положем восьмерку и снимем по очереди имеющиеся два занчения");
	push(summ(value, ONE)); //8
	printf("%d\n", ternaryToDecimal(pop()));
	printf("%d\n", ternaryToDecimal(pop()));
	puts("Запишим и прочтем данные используя память для инструкций на адрес 10 данные 33");
	writeBus(Text, decimalToTernary(10), decimalToTernary(33));
	printf("%d\n", ternaryToDecimal(readBus(Text, decimalToTernary(10))));
	puts("Запишим и прочтем в память для данных на адресс 5 данные 2");
	writeBus(Data, decimalToTernary(5), decimalToTernary(2));
	printf("%d\n", ternaryToDecimal(readBus(Data, decimalToTernary(5))));
	return 0;
}

Tryte_t decimalToTernary(T digit) {
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
	Stack.sp = &SP;		//потому, что при top == 0 невозможжно получить
	*Stack.sp = decimalToTernary(0); //данные по этому адресу с помощью функции pop
	Stack.bp = &BP;
	*Stack.bp = decimalToTernary(0);
}

T writeBus(Tryte_t *bus, Tryte_t addr, Tryte_t data) {
        memcpy((bus + ternaryToDecimal(addr)), &data, sizeof(Tryte_t));
        return 0;
}

Tryte_t readBus(Tryte_t *bus, Tryte_t addr) {
	Tryte_t tmp;
        memcpy(&tmp, (bus + ternaryToDecimal(addr)), sizeof(Tryte_t));
        return tmp;
}
