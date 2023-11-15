# Lab 07  - Race Conditions

## Lab 7-1
	
 	Lab 7-1 Files:

		7-1_lab.bin:		binary file for lab 7-1
		7-1_exploit.py:		python script used to exploit Lab 7-1
		7-1_flag.png:		screenshot of successful script execution and flag retrieval

	
	The target program for lab 7-1 is designed to securely read non-flag files. It performs several checks to ensure that the provided filename exists, is not a symbolic link, and doesn't contain the substring "flag.txt." If all checks pass, it opens and reads the file's content. However, there is a race condition vulnerability between the file checks and the opening of the file, which can be exploited to read the target file "flag.txt."

	The exploit for this lab leverages this race window by creating a file named "safe.txt" to pass the checks, and then creates a symbolic link with the same name "safe.txt" that points to the target file. The goal is that this switch from a regular file to a symbolic link happens within the race window, so that when the lab attempts to read the file, which it believes passes all the checks, it is instead a link to "flag.txt." This enables the exploit to access the "flag.txt" file, bypassing the security checks, due to the change in the file type within the race condition window.

## Lab 7-2
	
 	Lab 7-2 Files:

		7-2_lab.bin:		binary file for lab 7-2
		7-2_exploit.py:		python script used to exploit Lab 7-2
		7-2_flag.png:		screenshot of successful script execution and flag retrieval

	
	The target program for lab 7-2 is designed to create temporary copies of the "flag.txt" file in a secure manner and then delete these copies. However, there is a race condition vulnerability between copying the file and deleting the file. The exploit for this lab leverages this race window by creating a copy of the 'flag.txt' file to another location, before it is deleted. 

## Lab 7-3
	
 	Lab 7-3 Files:

		7-3_exploit.c:		c file used to exploit Lab 7-3

	The target program for lab 7-3 operates within the kernel space, and its primary objective is to manage user authentication and privilege escalation. First it handles user authentication through a set of predefined User IDs and passwords, by checking any incoming login credentials against these predefined values to determine if the user is a guest or an administrator. Then, if a user is authenticated as an administrator, the program performs privilege escalation, changing the Effective Group ID of the current process to a predefined value (LAB73WIN_ID). This change in group privileges grants the process the necessary credentials to access the 'flag.txt' file.
	
	However, there is a race condition vulnerability between the verification of user credentials and the EGID alteration. This vulnerability presents an opportunity for exploitationand gain admin privileges. The method involves providing valid login credentials to successfully pass the authentication check, but then modify the 
	userid field from USERID_GUEST to USERID_ADMIN before the priveleges are set.
	
	While I'm still in the process of understanding the exploit's inner workings, I encounter difficulties in debugging due to the inability to step through the program's execution. In my attempt to exploit this vulnerability, I've employed a multi-threaded approach:

		- Thread1 repeatedly dispatches valid guest credentials with the CMD_LOGIN command to satisfy the is_valid_account check.
		- Thread2 concurrently manipulates the userid field, changing it from USERID_GUEST to USERID_ADMIN during the brief race condition window.

	My goal is to have the userid set as USERID_GUEST during the checks, but changed to USERID_ADMIN before the priveleges are set. Unfortunately, I am unsure that my method of updating the local variable for the userid is reflected in the kernel variable. To address this, I'm actively studying the intricacies of IOCTL interfaces to gain a more comprehensive understanding. Once I've made further progress, I will update the exploit accordingly.

## Additional Notes

   - Each file is named in the format: "7-X_Title," where "X" corresponds to the lab number, and "Title" describes the file's purpose or content.
	
   - All python scripts require Python 3, pwntools
      > sudo apt-get install python3 <br>
      > pip install pwntools <br>
      *installation instructions assume Linux-based systems*
	
   - scripts can be executed using the format `python3 programName`. 
      > python3 7-2_script.py
