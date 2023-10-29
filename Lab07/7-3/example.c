// Compile: gcc -o example.bin example.c

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define DEVFILE		"lab73_login"

#define CMD_LOGIN	100

#define USERID_GUEST	9999
#define PASSWD_GUEST	123456

struct login_creds {
	long int userid;
	long int passwd;
};

struct login_creds lc;

int main(int argc, char *argv[]) {

	int fd;

	fd = open("/dev/"DEVFILE, O_RDWR);
	if (fd < 0) {
		perror("open");
		return 0;
	}

	lc.userid = USERID_GUEST;
	lc.passwd = PASSWD_GUEST;

	ioctl(fd, CMD_LOGIN, &lc);

	// Now run 'dmesg | tail' to see the login message

	return 0;

}
