#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
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

int main(int argc, char *argv[]) {

	int fd, r;
	struct stat st;
	char buff[32];

	init();

	if (argc != 2) {
		printf("Secure File Reader (v 0.1)\n");
		printf("Securely read non-flag files.\n\n");
		printf("Usage: %s <filename>\n", argv[0]);
		return 0;
	}

	// make sure the file actually exists

	if (lstat(argv[1], &st) < 0) {
		printf("Failed to open '%s'\n", argv[1]);
		return 0;
	}

	// make sure the user didn't create a symlink to the flag

	if ((st.st_mode & S_IFMT) != S_IFREG) {
		printf("Only regular files are allowed to be read.\n");
		return 0;
	}

	// make sure the user isn't trying to read the flag directly

	if (strstr(argv[1], "flag.txt") != NULL) {
		printf("Reading the flag.txt file is not allowed.\n");
		return 0;
	}

	// all checks passed!  read the file

	fd = open(argv[1], O_RDONLY);

	while ((r = read(fd, buff, 32)) > 0)
		write(0, buff, r);

	close(fd);

	return 0;

}
