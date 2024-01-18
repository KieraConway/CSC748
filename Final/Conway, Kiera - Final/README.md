# Final - Stone Guardian Login Wrapper
* December 2023 *
* Kiera Conway *

The Stone Guardian Login Wrapper is a simulated login system designed for educational purposes. The project includes a vulnerable C program and an accompanying exploit script that demonstrates the exploitation of identified security weaknesses.

## Included Files:
	README.md							documentation for the SG project [ You are Here :) ]
	flag								target string to indicate successful exploitation
	
	Makefile							automates compilation process for target program
	Stone_Guardian_Login_Wrapper.c		target source code
	Stone_Guardian_Login_Wrapper.bin	compiled binary executable for target

	sg_exploit.py						python script used to exploit target
	sg_exploit.png						screenshot of successful script execution and flag retrieval
	sg_functionality.png				screenshot of general functionality of target program


## Target
	
	The Stone Guardian Inc. offers a 100% secure login wrapper that provides an impenetrable authentication framework that can be easily integrated into various programs. Acting as a wrapper, this system enables companies to enhance the security of their existing applications by implementing robust login procedures. By seamlessly integrating this wrapper, organizations can leverage the authentication checks provided and seamlessly pass control to their specific programs, ensuring a standardized and secure login process tailored to their needs. Also, its completely secure - or is it?
	
	The program begins by prompting users for a username and password, which are then authenticated against a predetermined user library. Not only does the program verify the correct credentials, but it also validates the entered username adheres to the company-assigned format ("admin", "mgr_...", or "emp_..."). Since it is able to distinguish between user types — admin, manager, or employee — it can even grant varying levels of access based on this categorization. For example, Administrators are given shell access, whereas other users are directed to the program this wrapper encapsulates	(Or, it will, pending replacement of the placeholder with the specific program details).

	In line with the fundamental principles of a secure login system, the program extends support for password resets. During this process, a temporary PIN is generated and sent to the user through a simulated notification. (Again, pending replacement of the placeholder with the specific program details). This Super-Secure (tm) two-step authentication approach provides an additional layer of verification that is IMPOSSIBLE to bypass.
	
	
	In fact, The Stone Guardian Inc. login wrapper incorporates several software exploitation mitigations to fortify its security posture. Full RELRO (Relocation Read-Only) is enabled to safeguard against certain types of attacks by making the Global Offset Table (GOT) read-only after the dynamic linker has resolved its entries. The binary also contains a Stack Canary, which fortifies the stack against buffer overflow attacks by detecting any attempt to overwrite it. NX (No eXecute) is also enabled to prevent malicious hackers from attempting execute data on the stack through code injection attacks. Lastly,  Position Independent Executable (PIE) is enabled to randomize the programs base address and eliminate attacks that rely on predictable memory locations. This is shown below in the output of the `checksec` command:
	```
	[*] '/home/Stone_Guardian_Login_Wrapper.bin
	    Arch:     amd64-64-little
		RELRO:    Full RELRO
		Stack:    Canary found
		NX:       NX enabled
		PIE:      PIE enabled
	```
	
	Despite these mitigations, the Stone Guardian Inc. login wrapper exhibits two severe vulnerabilities. First, there is an uninitialized variable vulnerability during the pin reset process. In the `ResetAccount()` function, if the entered username does not conform to the company-assigned format, the variable `int code` is not created, and remains unintialized. Uninitialized variables are extremely dangerous as they can allow attackers to exploit memory contents in unpredictable ways. In this context, the absence of proper initialization presents the opportunity to set a custom pin to reset a password.
	
	The second critical vulnerability arises when the program prompts the user for a new password, by utilizing the unsafe `gets()` function - `gets()` is known for its vulnerability to buffer overflow attacks. Since it lacks bounds checking, attackers can potentially overwrite adjacent memory. In this context, the close proximity of the input field for the new password to the `username` input makes it a prime target for exploitation.
 

## Exploit
	
	### Vulnerability 1: Uninitialized Variable
	The provided exploit script is designed to target and exploit these vulnerabilities within the Stone Guardian Inc. login wrapper program to achieve unauthorized access. The script starts by simulating a login attempt (Option 1) and delivers a carefully crafted payload to hijack the PIN validation process. To pass the initial checks in the login process, the script delivers a valid username, specifically the administrator's username (admin). This is a crucial step as the program performs checks to verify that the entered username adheres to the company-assigned format ("admin", "mgr_", or "emp_"). By providing a valid username, the script ensures it passes the initial validation and progresses to the password prompt. This is vital as the final four bytes in the `UserLogin()` password buffer directly align the reset PIN. A basic visualization of this is shown below:
	
	+------------------------------------------------------------------------------------
	|							|			...				|			...				|
	|                           | (Password[00-07])			|			...				|
	|                           | (Password[08-15])			|			...				|
	|                           | (Password[16-23])			|			...				|
	| Stack (8-byte increments)	| (Password[24-32])			| **PIN**					| <-- Uninit Vulnerability
	|                           | (Username[00-07])			| (New Password[00-07])		|
	|           /\              | (Username[08-15])			| (New Password[08-15])		| 
	|          / |\             | (Username[16-23])			| (Reset Username[00-07])	| <-- Buffer Overflow Vulnerability
	|            |              | (Username[24-32])			| (Reset Username[08-15])	|
	|            |              | ($rbp)					| ($rbp)					|
	|                           | (return address)			| (return address)			|
	+------------------------------------------------------------------------------------
	|     Function Name         |		 UserLogin()		|		ResetAccount()		|
	+------------------------------------------------------------------------------------   	

	What this means, is that the script can craft a payload designed to manipulate this PIN and set it to any value. In the provided exploit, the payload `reset_pin_payload` consists of a sequence of 'A's to fill the password buffer and sets a predefined PIN of `1234`. 
	The exploit then selects the option to reset an account (Option 2) and intentionally triggers an uninitialized variable vulnerability within the `ResetAccount()` function. By providing an invalid username (one that does not adhere to the company-assigned format), the script bypasses the initialization of `int code`. This leaves the injected PIN from the previous step in the buffer, effectively hijacking the PIN validation process. Then, when the program asks for the reset PIN, the exploit resends the predefined PIN of `1234`. 

	### Vulnerability 2: Buffer Overflow
	Now that the reset PIN has been accepted, the program proceeds to reset the user's password. The next step of this script involves exploiting a buffer overflow vulnerability during this password reset process by leveraging a carefully crafted payload.  The first part of this payload involves setting the variable `new_password`. Since this password is essential for later use during the login process, it is constructed as a sequence of 'C's, followed by a null byte (b'\x00'). The purpose of this design is to ensure the password can be easily (1) remembered and (2) reentered when prompted. The null byte serves a dual purpose, as it prevents unintended characters from appearing in the new password and facilites the subsequent login process. Essentially, in the `UserLogin()` function, when a username/password is entered, a null character is automatically appended to the input. By incorporating the null byte in the initial payload, the script ensures that the password, crafted as a sequence of 'C's terminated by the null byte, aligns with the expected format during the login attempt. Simply put, it ensures the saved password will match the input when entered during the login process.


	Next, the script appends 'admin' to the payload. As shown in the previous visualization, the `new_password` is stored immediately adjacent to the username. This placement is crucial as it ensures precise targeting. Essentially, when the script executes a buffer overflow, it is able to strategically overwrite the username field with the valid username 'admin,' 
	which ensures the password reset is specifically associated with the 'admin' user. Following this manipulation, the payload is delivered, and the password associated with the 'admin' user is updated to the predefined value (a sequence of 15 'C's ).
	Finally, when the script reattempts the login process using the modified credentials, it seamlessly passes authentication checks and obtains shell access.  After successful execution, the script enters an interactive session, allowing the user to interact with the compromised program and obtain the flag.
	
	

## Additional Notes

- The Python script requires Python 3 and the `pwntools` library.
  - Installation: `sudo apt-get install python3`, `pip install pwntools` (Linux-based systems).

- Execute the script using the command: `python3 sg_exploit.py`.

- The target program can be run using `./Stone_Guardian_Login_Wrapper.bin`.

- Comments labeled as 'oops' within the target code provide hints about potential vulnerabilities.

- Consider organizing the code by moving functions to a separate header file for clarity and focusing on the exploitation process.

- The flag retrieval does not require elevated permissions. In a realistic CTF scenario, permissions should be modified to reflect the intended difficulty.

- This code is open and can be included in community repositories with proper attribution.

## Additional Notes

	- python script requires Python 3, pwntools
		> sudo apt-get install python3 <br>
		> pip install pwntools <br>
		*installation instructions assume Linux-based systems*
	
	- script can be executed using the format `python3 programName`. 
		> python3 sg_exploit.py

	- target program can be executed using `./Stone_Guardian_Login_Wrapper.bin`

	- target program contains comments labeled 'oops' to provide hints of vulnerabilities. These may be removed to increase difficulty
	
	- While some functions in the target program could be moved to a separate header file for cleaner code, they are included here for a comprehensive view of the program's functionality. Feel free to modify the code as needed for your specific use case, enhance code organization, or increase difficulty
	
	- the provided flag is accessible without sudo permissions; in a real exploit simulation, permissions should be adjusted for the CTF scenario
	
	- this project and its code are open and welcome to inclusion in community repositories, with proper attribution.
