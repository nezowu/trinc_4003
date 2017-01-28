#include <stdio.h>
#define STACK_S 10

typedef struct stack_t {
	int data[STACK_S];
	size_t size;
} Stack_t;

void push(Stack_t *stack, const T value) {
	stack->data[stack->size] = value;
	stack->size++;
}

int main(void) {
	push(
}

