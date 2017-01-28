#include <stdio.h>

typedef struct tryte_t {
	char *str;
	int dig;
	char ch;
	struct tryte_t *next;
	struct tryte_t *prev;
} Tryte_t;

void printing(Tryte_t *start) {
	Tryte_t *i = start;
	for(; i != NULL; i = i->next)
		printf("%s %d %c\n", i->str, i->dig, i->ch);
}

void printing_rev(Tryte_t *finish) {
	Tryte_t *i = finish;
	for(; i != NULL; i = i->prev)
		printf("%s %d %c\n", i->str, i->dig, i->ch);
}

int main(void) {
	Tryte_t one = {"one", 1, 'a', NULL};
	Tryte_t two = {"two", 2, 'b', NULL};
	Tryte_t three = {"three", 3, 'c', NULL};
	Tryte_t four = {"four", 4, 'd', NULL};
	one.next = &two;
	two.next = &three;
	three.next = &four;
	four.prev = &three;
	three.prev = &two;
	two.prev = &one;
	printing(&one);
	printing_rev(&four);
	return 0;
}
