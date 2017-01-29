/* Надо написать еще две функции call и ret
 * которые будут использовать pop и push
 * и в конечном варианте надо подставить
 * вместо данных определенную ранее структуру трайта.
 */
#include <stdio.h>
#include <stdlib.h>
#define STACK_S 10

typedef struct stack_t {
	unsigned short data[STACK_S];
	unsigned short size;
} Stack_t;

Stack_t stack;

void push(unsigned short value) {
	if (stack.size == STACK_S)
		exit(1);
	stack.data[stack.size] = value;
	stack.size++;
}

int pop() {
	if (stack.size == 0)
		exit(1);
	stack.size--;
	return stack.data[stack.size];
}

int main(void) {
	unsigned short digit1 = 1;
	unsigned short digit2 = 2;
	unsigned short digit3 = 5;
	push(digit1);
	push(digit2);
	push(digit3);
	printf("%hu\n", pop());
	printf("%hu\n", pop());
	printf("%hu\n", pop());
	return 0;
}
