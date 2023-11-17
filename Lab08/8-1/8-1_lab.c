#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

struct bow {
	int pull_weight;
	int length;
};

struct arrow {
	char type[64];
};

struct target {
	void (*hit)();
	char brand[32];
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

void debug_shell() {

	execl("/bin/bash", "/bin/bash", NULL);

}

void hit_action() {

	printf("Bullseye! Nice shot!\n");

}

// This function is a work in progress :)
void do_archery() {

	struct target *t;
	struct bow *b;
	struct arrow *a;

	// TODO: Add turns for each player
	// For now, just let the user take one shot

	printf("Setting up taget\n");
	t = malloc(sizeof(struct target));
	t->hit = hit_action;

	printf("Stringing bow\n");
	b = malloc(sizeof(struct bow));

	// let the user choose an arrow
	a = malloc(sizeof(struct arrow));
	printf("What type of arrow would you like to use?: ");
	scanf("%s", a->type);

	// TODO: Add different actions and hit probabilities depending on arrow type
	// for now, just assume it hits

	t->hit();

}

void welcome_players() {

	char name[1024];
	char *players[16] = {0};
	int num;

	printf("Who will be competing today?\n");

	// load a list of player names
	for (num=0; num<16; num++) {

		printf("Enter player name (or 'done' to finish): ");
		scanf("%1023s", name); // safe

		if (strcmp(name, "done") == 0)
			break;

		players[num] = malloc(strlen(name) + 1);
		strcpy(players[num], name); // safe

	}

	printf("\n");

	// welcome all of those players
	for (num=0; num<16; num++) {

		if (players[num] == NULL)
			continue;

		printf("Welcome %s!  Good luck!\n", players[num]);
		free(players[num]);

	}

	printf("\nGame starting...\n\n");

}

int main() {

	init();

	printf("\n");
	printf(" >>>------->    (@)\n");
	printf("                / \\\n");
	printf("\n");
	printf("Welcome to the archery range!\n\n");

	welcome_players();

	do_archery();

	return 0;

}
