#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

char user[16] = "guest";

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

	int i;

	scanf("%d", &i);
	while (getchar() != '\n');

	return i;

}

int main() {

	char *notes[16] = {0};
	int choice, tmp, i;

	init();

	printf("Note app v0.1\n\n");

	while (1) {

		printf("What would you like to do?: ");
		printf("(1) New, (2) View, (3) Delete, (4) Edit, (5) Debug shell\n");
		printf("Choice: ");
		choice = get_int();

		switch(choice) {

			case 1:	// New
				for (i=0; i<16 && notes[i]; i++);
				if (i < 16) {
					notes[i] = malloc(32);
					printf("Contents: ");
					scanf("%31s", notes[i]);		// safe! no overflow here
					printf("Note saved! (ID#%d)\n", i);
				} else {
					printf("sorry, too many notes\n");
				}
				break;

			case 2: // View
				printf("Note ID?: ");
				choice = get_int();
				if (choice >= 0 && choice < 16)
					printf("Contents: %s\n", notes[choice]);
				else
					printf("Invalid note ID\n");
				break;

			case 3: // Delete
				printf("Note ID?: ");
				choice = get_int();
				if (choice >= 0 && choice < 16)
					free(notes[choice]);
				else
					printf("Invalid note ID\n");
				break;

			case 4: // Edit
				printf("Note ID?: ");
				choice = get_int();
				if (choice >= 0 && choice < 16) {
					printf("New contents: ");
					scanf("%31s", notes[choice]);		// safe! no overflow here
				} else {
					printf("Invalid note ID\n");
				}
				break;

			case 5: // Debug shell
				if (strcmp(user, "admin") == 0)
					execl("/bin/bash", "/bin/bash", NULL);
				else
					printf("Sorry, user '%s' isn't allowed to start a debug shell\n", user);
				break;

			default:
				printf("Invalid choice\n");

		}

	}

	return 0;

}
