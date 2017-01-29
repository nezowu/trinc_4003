#include <stdio.h>
#define STACK_S 10

typedef int T;

typedef struct stack_t {
	T data[STACK_S];
	size_t size;
} Stack_t;

Stack_t stack;

void push(Stack_t *stack, T value) {
	stack->data[stack->size] = value;
	stack->size++;
}

T pop(Stack_t *stack) {
//	if (stack->size == 0) {
//		exit(STACK_UNDERFLOW);
//	}
	stack->size--;
	return stack->data[stack->size];
}

int main(void) {
	T digit1 = 1;
	T digit2 = 2;
	T digit3 = 5;
	push(&stack, digit1);
	push(&stack, digit2);
	push(&stack, digit3);
	printf("%d %d %d\n", pop(&stack), pop(&stack), pop(&stack));
	return 0;
}
