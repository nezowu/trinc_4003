#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#define STR1 "Я функция, записала в соккет"

int sockets[2];
char buff[1024];
char stove[1024];


void chanal(void) {
	int pid, count = 0;
	switch(pid = fork()) {
		case -1:
			perror("fork()");
			exit(EXIT_FAILURE);
		case 0:
			close(sockets[1]);
			while(count != 2) {
				read(sockets[0], buff, 1024);
				printf("%s %s\n", buff, "Я функция, прочитала из соккета");
			}
		default:
			close(sockets[0]);
			while((scanf("%1023[^\n]%*c", stove)) == 1) {
				write(sockets[1], stove, 1024);
				printf("%s\n", "Я главный процесс, записал в соккет");
				count++;
			}
	}
}

int main(void) {
	socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
	chanal();
	puts("Хорошо");
	return 0;
}
