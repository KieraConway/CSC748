#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

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

void copy_file(char *src, char *dst) {

	struct stat st;
	int sfd, dfd;

	lstat(src, &st);

	sfd = open(src, O_RDONLY);
	dfd = open(dst, O_RDWR|O_CREAT, 0644);

	if (sfd < 0 || dfd < 0) {
		printf("File IO error\n");
		return;
	}

	sendfile(dfd, sfd, NULL, st.st_size);

	close(sfd);
	close(dfd);

}

int main(int argc, char *argv[]) {

	int pid, status;
	char tempfile[] = "/dev/shm/flag.txt.XXXXXX";

	init();

	printf("Secure Flag Deleter (v 0.1)\n");
	printf("Securely delete copies of flag.txt.\n\n");

	printf("Making a copy of the flag.txt for deletion...\n");
	mktemp(tempfile);
	copy_file("/home/lab7-2/flag.txt", tempfile);

	printf("Deleting flag.txt...\n");
	unlink(tempfile);

	return 0;

}
