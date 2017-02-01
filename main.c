#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned short T;

typedef struct tryte_t {
	uint8_t three:2, two:2, one:2, ou:2;
} Tryte_t;

Tryte_t r0;
Tryte_t r1;
Tryte_t r2;
Tryte_t r3;
Tryte_t rf; // регистр флагов

Tryte_t summ(Tryte_t, Tryte_t);
T less(Tryte_t, Tryte_t);
T equal(Tryte_t, Tryte_t);
Tryte_t sub(Tryte_t, Tryte_t);
T ternary_to_decimal(Tryte_t *);
Tryte_t decimal_to_ternary(T);

int main(int argc, char *argv[]) {
	r0.three = 0, r0.two = 0, r0.one = 0, r0.ou = 0;
	r1.three = 0, r1.two = 0, r1.one = 0, r1.ou = 1;
	r2.three = 0, r2.two = 2, r2.one = 2, r2.ou = 2;
	r3.three = 0, r3.two = 1, r3.one = 1, r3.ou = 2;
	rf.three = 0, rf.two = 0, rf.one = 0, rf.ou = 0; // регистр флагов

//	printf("%d\n", less(r0, r1));
//	printf("%d\n", equal(r0, r1));

	r0 = summ(r0, r1);
	printf("%d%d%d%de%d\n", r0.three, r0.two, r0.one, r0.ou, rf.ou);
	printf("%d\n", ternary_to_decimal(&r0));
//	r0 = sub(r2, r3);
//	printf("%d%d%d%de%d\n", r0.three, r0.two, r0.one, r0.ou, rf.one);
	// загружаем двоичную программу в память.
//	FILE *prog;
//	prog = fopen(argv[1], "r");
//	if(!prog) {
//		perror("can't open programm file");
//		return(1);
//	}
//	fwrite(&mem, sizeof(mem), 1, prog);
//	printf("%d %d %d %d\n", mem.ou, mem.one, mem.two, mem.three);
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
		rf.ou = sum;
		reg0.ou = reg0.one;
		reg0.one = reg0.two;
		reg0.two = reg0.three;
		reg0.three = sum;
	}
	return reg0;
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

T equal(Tryte_t dig0, Tryte_t dig1) { // ==
        if(dig0.ou == dig1.ou && dig0.one == dig1.one && dig0.two == dig1.two && dig0.three == dig1.three)
                return 1;
        else
                return 0;
}


Tryte_t sub(Tryte_t reg0, Tryte_t reg1) { // -
        T sub = 0;
        if(less(reg0, reg1)) {
                Tryte_t temp; 
                memcpy(&temp, &reg0, 1);
                memcpy(&reg0, &reg1, 1);
                memcpy(&reg1, &temp, 1);
                rf.one = 1;
        } else  
                rf.one = 0;
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
