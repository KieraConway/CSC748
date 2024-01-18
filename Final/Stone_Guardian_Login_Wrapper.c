/* -----------------------------------------------------------------------------
    Stone Guardian Login Wrapper
    Vulnerable C Program
    Dakota State University
    CSC 748 - Final

    Kiera Conway
----------------------------------------------------------------------------- */
/* Standard Libraries */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/** ------------------------------ Prototypes ------------------------------ **/

/*** Setup Functions ***/
void init();                                    // program initialization tasks
void sig_handler(int signum);                   // signal handling, specifically for timeout
void generateAdminPassword(char *password);     // random password generation for admin

/*** Input Handling Functions ***/
int get_int();                                  // input parsing and extracting

/*** Authentication Functions ***/
int findUserIndex(const char *username);        // user index locator for userLibrary array
int Authenticate(const char *enteredUsername,
                 const char *enteredPassword);  // user credential authentication

/*** User Management Functions ***/
void UserLogin();                               // user login process manager
void ResetAccount();                            // user password reset manager
int GeneratePinAndNotify(const char *userType); // pin generation and notification

/** ------------------------ Typedefs and Structs ------------------------ **/
// user information structure
struct User {
    char username[32];
    char password[32];
};

// user library for simulated company
struct User userLibrary[] = {
        {"admin", ""},
        {"mgr_2132", "DontTurnYourBack"},
        {"emp_0215", "DontLookAway"},
        {"emp_2165", "AndDontBlink"},
        {"emp_9671", "GoodLuck"},
};


/** ----------------------------- Functions ----------------------------- **/

/* ------------------------------------------------------------------------
  Name -            init
  Purpose -         Performs program initialization tasks
  Parameters -      none
  Returns -         none
  Side Effects -    Sets up a timeout alarm, handles SIGALRM with sig_handler,
                    adjusts input/output buffering, changes directory to HOME,
                    and generates a random password for the admin user
  Credits -         Originally implemented by Dr. Andrew Kramer, DSU
  ----------------------------------------------------------------------- */
void init() {
    alarm(60);							// Set a timeout alarm for 60 seconds
    signal(SIGALRM, sig_handler);		// Handle SIGALRM with the sig_handler function

    setvbuf(stdin, NULL, _IONBF, 0);    // Disable input buffering
    setvbuf(stdout, NULL, _IONBF, 0);   // Disable output buffering
    setvbuf(stderr, NULL, _IONBF, 0);   // Disable error output buffering

    chdir(getenv("HOME"));				// Change directory to HOME

    srand((unsigned int)time(NULL));
    generateAdminPassword(userLibrary[0].password);	// Generate random password for admin
}


/* ------------------------------------------------------------------------
  Name -            sig_handler
  Purpose -         Handles signals, specifically for timeout.
  Parameters -      signum: Signal number indicating the received signal
  Returns -         none
  Side Effects -    Exits the program after printing a timeout message
  Credits -         Originally implemented by Dr. Andrew Kramer, DSU
  ----------------------------------------------------------------------- */
void sig_handler(int signum) {
    printf("Timeout\n");
    exit(0);
}


/* ------------------------------------------------------------------------
  Name -            generateAdminPassword
  Purpose -         generates random 10-digit string for admin password
  Parameters -      password: Pointer to where password will be stored
  Returns -         none
  Side Effects -    modifies content of 'password' array
  ----------------------------------------------------------------------- */
void generateAdminPassword(char *password) {

    snprintf(password,
             32,
             "%09d",
             rand() % 1000000000);
}


/* ------------------------------------------------------------------------
  Name -            get_int
  Purpose -         reads an integer from standard input
  Parameters -      none
  Returns -         the integer read from the input
  Side Effects -    consumes any additional characters in input buffer
  Credits -         Originally implemented by Dr. Andrew Kramer, DSU
  ----------------------------------------------------------------------- */
int get_int() {
    int i;
    scanf("%d", &i);

    while ((getchar()) != '\n');   // clear additional char from input buffer

    return i;
}


/* ------------------------------------------------------------------------
  Name -            findUserIndex
  Purpose -         finds index of username in the userLibrary array
  Parameters -      username:  username to search for
  Returns -          i:  index of user, if found
                    -1:  user not found
  Side Effects -    none
  ----------------------------------------------------------------------- */
int findUserIndex(const char *username) {
    for (int i = 0; i < sizeof(userLibrary) / sizeof(userLibrary[0]); ++i) {
        if (strcmp(username, userLibrary[i].username) == 0) {
            return i;	// user found, return index
        }
    }
    return -1;			// user not found
}


/* ------------------------------------------------------------------------
  Name -            Authenticate
  Purpose -         Performs user authentication
  Parameters -      enteredUsername:    Username to Authenticate
                    enteredPassword:    Password to Authenticate
  Returns -         1: Authentication Successful
                    0: Authentication Failed
  Side Effects -    none
  ----------------------------------------------------------------------- */
int Authenticate(const char *enteredUsername, const char *enteredPassword) {
    for (int i = 0; i < sizeof(userLibrary) / sizeof(userLibrary[0]); ++i) {
        if (strcmp(enteredUsername, userLibrary[i].username) == 0 &&
            strcmp(enteredPassword, userLibrary[i].password) == 0) {
            return 1;   // authentication successful
        }
    }
    return 0;           // authentication failed
}


/* ------------------------------------------------------------------------
  Name -            UserLogin
  Purpose -         handles user login functionality
  Parameters -      none
  Returns -         none
  Side Effects -    prompts user for username and password,
                    performs authentication, and
                    provides access based on the user type.
  ----------------------------------------------------------------------- */
void UserLogin() {
    /*** Function Initialization ***/
    char password[32], username[32];


    /*** Prompt User for Username ***/
    printf("enter username > ");
    scanf("%31s", username);

    /* Error Check: Verify Format
     *
     * Check to verify that the entered username
     * adheres to the company-assigned format
     * ("admin", "mgr_", or "emp_")
     */
    if (strncmp(username, "admin", 5) != 0 &&
    strncmp(username, "mgr_", 4) != 0 &&
    strncmp(username, "emp_", 4) != 0) {
        printf("Invalid username format. Returning to main.\n");
        return;
    }


    /*** Prompt User for Password ***/
    printf("enter password > ");
    scanf("%31s", password);


    /*** Perform Authentication ***/
    if (Authenticate(username, password)) {				// if authenticated ..
        printf("Authentication successful.\n");

        /* Access Handling based on User Type */
        if (strncmp(username, "admin", 5) == 0) {		// verify user type
            printf("Shell access granted.\n");
            execl("/bin/bash", "/bin/bash", NULL);		//if admin, give shell

        }
        else{
            printf("Login Successful.\n");				//else, pass to company program


        /*
		 * Stone Gaurdian is a login wrapper program 
		 *
         * Pass control to the target program here 
		 * for 100% completely secure access.
		 *
         * ie: Replace "/path/to/target_program" 
		 * with the actual path to your wrapped program.
		 *
		 * > system("/path/to/target_program");
		 *		
		 * [SG inc.]
		 */
        }

    }
    else {
        printf("Authentication failed. Returning to main.\n");        // if authentication fails, return to main
    }
}


/* ------------------------------------------------------------------------
  Name -            ResetAccount
  Purpose -         handles password reset functionality
  Parameters -      none
  Returns -         none
  Side Effects -    modifies user passwords based on the reset process
  ----------------------------------------------------------------------- */
void ResetAccount() {
    /*** Function Initialization ***/
    char newPassword[16], username[16];
    int input, code, userIndex;

    /*** Prompt User for Username ***/
    printf("enter username > ");
    scanf("%31s", username);

    /*** Determine User type and Generate Pin ***/
    if (strncmp(username, "admin", 5) == 0) {
        code = GeneratePinAndNotify("admin");
    } else if (strncmp(username, "mgr_", 4) == 0) {
        code = GeneratePinAndNotify("manager");
    } else if (strncmp(username, "emp_", 4) == 0) {
        code = GeneratePinAndNotify("employee");
    }   // oops...

    /*** Prompt for Pin ***/
    printf("Enter pin > ");
    scanf("%d", &input);


    /*** Reset Password if Correct Pin ***/
    if (input == code){

        printf("Reset pin accepted. Proceeding with password reset.\n");
        getchar();								// clear newline from input buffer

        /* Prompt User for New Password */
        printf("Enter new password > ");
        gets(newPassword);						//oops

        /* Locate User in Array */
        userIndex = findUserIndex(username);
        if (userIndex != -1) {

            /* Assign New Password to User */
            strcpy(userLibrary[userIndex].password, newPassword);
            printf("Password reset successful for user: %s\n", username);
        }
        else {
            printf("User not found. Password reset failed.\n");
        }
    }
    else {
        printf("Incorrect pin. Access denied.\n");
    }

}


/* ------------------------------------------------------------------------
  Name -            GeneratePinAndNotify
  Purpose -         generates a temporary pin and sends notification to user
  Parameters -      userType: Type of user ("admin", "manager", "employee")
  Returns -         temporary pin for user verification
  Side Effects -    none
  ----------------------------------------------------------------------- */
int GeneratePinAndNotify(const char *userType){
    /*** Function Initialization ***/
    int tempPin, mod, rndm;

    /*** Pin Generation ***/
    mod = 10000;
    rndm = rand();
    tempPin = rndm % mod;

    /*** User Notification ***/
    if (strcmp(userType, "admin") == 0) {
        //sendEmail("admin", "Password Reset", tempPin);		todo
        printf("Temporary pin sent to administrator account on file.\n");
    }

    else if (strcmp(userType, "manager") == 0) {
        //sendEmail("manager", "Password Reset", tempPin);		todo
        printf("Temporary pin sent to manager account on file.\n");
    }
    else if (strcmp(userType, "employee") == 0) {
        //sendEmail("HR", "Password Reset", tempPin);			todo
        printf("Email sent to HR, please contact your HR representative.\n");
    }

    return tempPin;
}


/* ------------------------------------------------------------------------
  Name -            main
  Purpose -         entry point for the Stone Guardian Inc. login wrapper
  Parameters -      none
  Returns -         0: successful program execution
  Side Effects -    executes login or password reset based on selection
  ----------------------------------------------------------------------- */
int main() {
    /*** Function Initialization ***/
    init();
    int choice = 0;

    /*** Display Option Menu ***/
    printf("\n Welcome to Stone Guardian Inc.\n\n");
    printf("     [1] Login\n");
    printf("     [2] Reset Password\n");
    printf("     [3] Exit\n\n");

    /*** User Interaction Loop ***/
    while (1) {
        printf(" > ");
        choice = get_int();

        switch (choice) {
            case 1:                     // [1] User Login
                UserLogin();
                break;
            case 2:                     // [2] Password Reset
                ResetAccount();
                break;
            case 3:                     // [3] Exit Program
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
