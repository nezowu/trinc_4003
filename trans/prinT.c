#include "tryte.h"

int main() {
	Tryte_t temp = {0, 0, 0, 0};
	for(T i = 0; i < N; i++) {
		printf("%d %d %d %d\t%d\n", temp.ou, temp.one, temp.two, temp.three, i);
		temp = summ(temp, ONE);
	}
	return 0;
}
