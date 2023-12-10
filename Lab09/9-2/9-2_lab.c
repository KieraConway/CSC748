#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

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

void get_string(char *s, int len) {

	int i;
	char c;

	// read up to (but not including) the newline
	for (i=0; i<len&&(c=getchar())!='\n'; i++)
		s[i] = c;

	// null terminate the string
	s[i] = '\0';

}

int main() {

	char *notes[16] = {0}, *filename;
	int choice, tmp, i, size;

	init();

	printf("Note app v0.3\n\n");

	while (1) {

		printf("What would you like to do?: ");
		printf("(1) New, (2) Delete, (3) Setup filename, (4) Read file\n");
		printf("Choice: ");
		choice = get_int();

		switch(choice) {

			case 1:	// New
				for (i=0; i<16 && notes[i]; i++);
				if (i < 16) {
					printf("Size: ");
					size = get_int();
					notes[i] = malloc(size);
					printf("Contents: ");
					get_string(notes[i], size+1);		// Whoops!
					printf("Note saved! (ID#%d)\n", i);
				} else {
					printf("sorry, too many notes\n");
				}
				break;

			case 2: // Delete
				printf("Note ID?: ");
				choice = get_int();
				if (choice >= 0 && choice < 16 && notes[choice] != NULL) {
					free(notes[choice]);
					notes[choice] = NULL;
				} else
					printf("Invalid note ID\n");
				break;

			case 3: // Setup filename
				filename = strdup("not_the_flag.txt");
				printf("Safe filename set!\n");
				break;

			case 4: // Read file
				printf("File contents: ");
				execl("/usr/bin/cat", "/usr/bin/cat", filename, NULL);
				break;

			default:
				printf("Invalid choice\n");

		}

	}

	return 0;

}
