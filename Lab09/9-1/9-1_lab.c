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

	FILE *fp;
	char *notes[32] = {0}, *flag;
	int choice, tmp, i;

	init();

	printf("Note app v0.2\n\n");
	printf("CHANGELOG:\n");
	printf("  Patched use-after-free vulnerability when editing notes\n");
	printf("  Increased number of notes from 16 to 32!\n");
	printf("\n");

	while (1) {

		printf("What would you like to do?: ");
		printf("(1) New, (2) View, (3) Delete, (4) Edit, (5) Load flag into memory\n");
		printf("Choice: ");
		choice = get_int();

		switch(choice) {

			case 1:	// New
				for (i=0; i<32 && notes[i]; i++);
				if (i < 32) {
					notes[i] = malloc(64);
					printf("Contents: ");
					scanf("%63s", notes[i]);		// safe! no overflow here
					printf("Note saved! (ID#%d)\n", i);
				} else {
					printf("sorry, too many notes\n");
				}
				break;

			case 2: // View
				printf("Note ID?: ");
				choice = get_int();
				if (choice >= 0 && choice < 32) {
					printf("Contents: ");
					write(1, notes[choice], 64);
				} else
					printf("Invalid note ID\n");
				break;

			case 3: // Delete
				printf("Note ID?: ");
				choice = get_int();
				if (choice >= 0 && choice < 32)
					free(notes[choice]);
				else
					printf("Invalid note ID\n");
				break;

			case 4: // Edit
				printf("Hacker tool, not allowed! >:(\n");
				break;

			case 5: // Load flag into memory
				fp = fopen("flag.txt", "r");
				flag = malloc(64);
				fgets(flag, 64, fp);
				fclose(fp);
				break;

			default:
				printf("Invalid choice\n");

		}

	}

	return 0;

}

