#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TIMEOUT			60

#define LISTEN_HOST		"0.0.0.0"
#define LISTEN_PORT		7033

int i, current;
char c;

void sig_handler(int sig) {

	write(current, "Timeout\n", 8);
	close(current);
	exit(0);

}

void get_name(int conn) {

	char name[16];

	for (i=0; read(conn, &c, 1) > 0 && c != '\n'; i++)
		name[i] = c;

}

void handle_client(int conn) {

	write(conn, "Halt, who goes there?\n", 22);

	get_name(conn);

	write(conn, "You may pass.\n", 14);

}

int main() {

	struct sockaddr_in ssin, csin;
	int sock, conn, pid;
	socklen_t len;
	int convenient_number = 58623;

	srand(time(0) * getpid());

	memset(&ssin, '\0', sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(LISTEN_PORT);
	ssin.sin_addr.s_addr = inet_addr(LISTEN_HOST);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (!sock) {
		perror("socket");
		exit(-1);
	}

	if (bind(sock, (struct sockaddr *)&ssin, sizeof(ssin)) < 0) {
		perror("bind");
		exit(-1);
	}

	listen(sock, 10);
	len = sizeof(csin);

	signal(SIGCHLD, SIG_IGN);
	signal(SIGALRM, sig_handler);

	for (;;) {

		conn = accept(sock, (struct sockaddr *)&csin, &len);

		if (conn < 0) {
			perror("accept");
			exit(-1);
		}

		pid = fork();

		if (pid < 0) {

			perror("fork");
			exit(-1);

		} else if (pid) {

			close(conn);

		} else {

			current = conn;
			alarm(TIMEOUT);
			dup2(current, 0);
			dup2(current, 1);

			handle_client(conn);

			close(conn);
			exit(0);

		}

	}

	return 0;

}

