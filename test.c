#include <stdio.h>
#include <stdint.h>

typedef struct tryte_t {
	uint8_t dig0:2;
	uint8_t dig1:2;
	uint8_t dig2:2;
	uint8_t dig3:2;
} Tryte_t;


int main(void) {
	Tryte_t one;
	Tryte_t ou;
//	Tryte_t two;
	ou.dig3 = 2; //00
	one.dig3 = 2; //01
//	two.dig3 = 2; //10
//	three.dig3 = 3; //11
	printf("%d\n", one.dig3 ^ ou.dig3);
	printf("%d\n", one.dig3 | ou.dig3);
	printf("%d\n", one.dig3 & ou.dig3);

//	printf("%d\n", one.dig3);
	return 0;
}
// функция больше.
unsigned short less(Tryte_t dig0, Tryte_t dig1) {
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
				else
					return 0;
			}
		}
	}
	return 0;
}

unsigned short equal(Tryte_t dig0, Tryte_t dig1) {
	if(dig0.ou + dig0.one + dig0.two + dig0.three == dig1.ou + dig1.one + dig1.two + dig1.three)
		return 1;
	else
		return 0;
}

Tryte_t sub(Tryte_t reg0, Tryte_t reg1) {
	unsigned short sub = 0;
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
