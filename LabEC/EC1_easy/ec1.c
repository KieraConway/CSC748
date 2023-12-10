/*
 * Finger server.
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <signal.h>

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
 
int fatal(char *prog, char *s) {
	fprintf(stderr, "%s: ", prog);
	perror(s);
	exit(1);
 }

int main(int argc, char *argv[]) {
	register char *sp;
	
	char line[512];
	//    struct sockaddr sin;
	int i, p[2], pid, status;
	FILE *fp;
	char *av[4];
 
	init();
 
	//    i = sizeof (sin);
	//    if (getpeername(0, &sin, &i) < 0)
	//	   fatal(argv[0], "getpeername");

	line[0] = '\0';		//init first char of line buffer to the null
	gets(line);			//read line from the standard input
	sp = line;			//pointer to beginning of line buffer
	av[0] = "finger";	//Init first element of the av with string "finger" - This is command that will be executed in child process, subsequent elements are arguments passed to this command
	i = 1;				//index in the av array where new args are added (starts at 1 because the 0th index is already assigned  to "finger"
	
	
	
	
	// // // // // // // // // // // // // //
	//parse input stored in the line buffer 
	//to construct an argument vector (av) 
	//for the "finger" command.
	// // // // // // // // // // // // // //
	while (1) {						//  iterate over input characters
		
		/*Skip Whitespace*/
		while (isspace(*sp)){	
			sp++;					// skip any leading whitespace characters
		}
			
			
		/*Check for End of Input*/			
		if (!*sp){
			break;					//If current char is null terminator ('\0') (end of string), break
		}
			
		/*Handle "/W" or "/w" Option*/			
		if (*sp == '/' && (sp[1] == 'W' || sp[1] == 'w')) {				//If current character is '/' AND next char (sp[1]) is either 'W' or 'w'...
			
			sp += 2;			//increments sp by 2 and 
			av[i++] = "-l";		//assign the "-l" to the av array at index i
			
			//a flag for the "finger" command ?
		}
		
		
		/*Handling Non-Whitespace Characters*/				
		if (*sp && !isspace(*sp)) {						//If current char is not whitespace and not null...
			av[i++] = sp;								//Assign current position (sp) to av[i++] (indicates start of a new argument in the argument vector)
			
			/* traverse characters */ 
			while (*sp && !isspace(*sp)){		//traverse until a whitespace char or null terminator is encountered
			  sp++;
			}
			
			/* terminate current argument */
			*sp = '\0';			//encountered whitespace is replaced with a null terminator ('\0')
		}
	}
	
	
	av[i] = 0;	//mark the end of the argument vector (av) to indicate end of arguments for command

	
	/* Create Pipe */
	if (pipe(p) < 0)
		fatal(argv[0], "pipe");
	
	// Creates a pipe using the pipe syscall. 
	// If the pipe creation fails (returns a value less than 0), 
	// call fatal function to print error msg and terminate program
	
	//Pipe Notes:
	// pipe is a form of interprocess communication 
	// it allows one proc to send data to another proc
	//
	//it has two ends:
	//	Read End	(p[0]): Where data is read from the pipe (This program - the parent process uses this end to read the output of the "finger" command executed by the child process after forking)
	//	Write End	(p[1]): Where data is written into the pip e(This program - the child process writes its stdout to this end)
	
	
	/* Fork Child Proc */
	if ((pid = fork()) == 0) {
		close(p[0]);			//Closes read end of the pipe (p[0])
		
		
		if (p[1] != 1) {		//if write end of pipe (p[1]) is not equal to file descriptor 1 (standard output)
			
		
			//dup2() syscall duplicates an existing file descriptor to another specified file descriptor
			// 
			//dup2(oldfd, newfd)
			//
			//	oldfd: The fd to be duplicated.
			//	newfd: The fd to which oldfd should be duplicated.
			//
			//dup2(p[1], 1) line duplicates the write end of pipe (p[1]) to file descriptor 1 (stdout), 
			//i.e. redirects standard output of child proc to the write end of the pipe.
			
			dup2(p[1], 1);

			close(p[1]);	//original fd p[1] is closed (duplicate remains open)
			
		}
		
		
		/* Execute Finger */	
		execv("/usr/bin/finger", av);		//"finger" command is executed with the provided argument vector (av) using execv.
		_exit(1);							//If execv fails, child proc will exit
	}

	
	if (pid == -1){							//parent: checks if forking of child failed (returns -1)
		fatal(argv[0], "fork");				//If true, call fatal function to print error msg and terminate program
	}

	
	close(p[1]);							//parent: close write end of the pipe (p[1]), as it's not needed for writing in parent
	
	
	if ((fp = fdopen(p[0], "r")) == NULL)	//parent: associate read end of pipe (p[0]) with a FILE stream (fp) using fdopen. 
		fatal(argv[0], "fdopen");			//if fails, call fatal function to print error msg and terminate program.
	
	while ((i = getc(fp)) != EOF) {			//parent: read char from fp until EOF is reached
	
		//for each character:
	
		if (i == '\n')			//if char is newline
			putchar('\r');		//print a carriage return ('\r') to simulate a new line.		
			
		putchar(i);				//print char
	}
	
	
	fclose(fp);		//parent: Close fp after reading is complete
	
	while ((i = wait(&status)) != pid && i != -1);	//parent: waits for the child to complete (continues until true)

	return(0);
 }


/*
Functionality:


The program emulates the execution of the "finger" command securely by forking a child process, redirecting its standard output to a pipe, and capturing the output in the parent process. 

The user provides input, and the program constructs an argument vector for the "finger" command. 

After creating the communication pipe, the child process is spawned, and its standard output is directed to the pipe.

In the parent process, the read end of the pipe is associated with a FILE stream, allowing the program to read and slightly modify the output. 

Specifically, for each newline character encountered in the "finger" command's output, a carriage return is printed before the newline character. 

This ensures proper formatting of the output. 

The program then cleans up resources, waits for the child process to complete, and exits. 

Overall, the program facilitates the execution of the "finger" command, capturing its output and making subtle adjustments for presentation purposes.


Finger Command:

command-line tool used in Unix-like operating systems to gather information about users. 
It provides details about users who are currently logged in, as well as information about a specific user if their username is provided as an argument.

The information displayed typically includes the user's login name, full name, terminal, idle time, login time, office location, and more. 

The finger command is a tool for system administrators or users to quickly check who is currently using the system or obtain information about specific users.

*/