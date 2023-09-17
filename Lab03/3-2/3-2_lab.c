#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define GUEST_ID 999
#define ROOT_ID 1337

struct user_record {
	char name[28];
	int id;
};

void sig_handler(int signum) {

	printf("Timeout\n");
	exit(0);

}

void init() {

	alarm(60);
	signal(SIGALRM, sig_handler);

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	chdir(getenv("HOME"));

}

int get_int() {

	int r;

	scanf(" %d", &r);
	while(getchar() != '\n');

	return r;

}

int main() {

	int choice;
	struct user_record u = {
		"Guest123",
		GUEST_ID
	};

	init();

	printf("Welcome, you are logged in as '%s'\n", u.name);

	while(1) {

		printf("\nHow can I help you, %s?\n", u.name);
		printf(" (1) Change username\n");
		printf(" (2) Switch to root account\n");
		printf(" (3) Start a debug shell\n");
		printf("Choice: ");
		choice = get_int();

		if (choice == 1) {

			printf("Enter new username: ");
			scanf("%s", u.name);

		} else if (choice == 2) {

			printf("Sorry, root account is currently disabled\n");

		} else if (choice == 3) {

			if (u.id == GUEST_ID) {
				printf("Sorry, guests aren't allowed to use the debug shell\n");
			} else if (u.id == ROOT_ID) {
				printf("Starting debug shell\n");
				execl("/bin/bash", "/bin/bash", NULL);
			} else {
				printf("Unrecognized user type\n");
			}

		} else {
			printf("Unknown option\n");
		}

	}

	return 0;

}
