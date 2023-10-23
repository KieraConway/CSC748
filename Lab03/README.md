# Lab 03 - Stack Cookie

## Lab 3-1

	Lab 3-1 Files:

		3-1_lab.bin:		binary file for lab 3-1
		3-1_exploit.py:		python script used to exploit Lab 3-1
		3-1_flag.png:		screenshot of successful script execution and flag retrieval

   The exploit for this lab establishes a connection to a remote server and interacts with the binary, where it then exploits a vulnerability to leak the stack cookie. Prior to initiating the exploit, Step 1 involves utilizing the hexdump function to examine the program's memory and pinpoint the stack cookie's location. During which, it is determined that the cookie is located between "price:" and a newline (0x0a) character. This knowledge enables the pwn library to locate and extract the cookie's value from the program's memory. 
	
   Once this is accomplished, the exploit sends the payload in parts: first the buffer fill consisting of 24 'A' characters, followed by the discovered cookie value, the address necessary for executing the specified opcode (leveraging 0xffe4 to represent 'JMP RSP'), and followed finally by the shellcode. 
	
   To activate the modified return address, the script selects option 4 within the target program, initiating a program exit. After successful execution, the script enters an interactive session, allowing the user to interact with the compromised program and obtain the flag.


## Lab 3-2

	Lab 3-2 Files:
	
		3-2_lab.bin:				binary file for lab 3-2
		3-2_exploit.py:				python script used to exploit lab 3-2
		3-2_flag.png:				screenshot of successful script execution and flag retrieval

	
   The exploit for this lab establishes a connection to a remote server and interacts with the binary, where it then exploits a vulnerability that results in escalating privileges to the root user. By selecting option 1 in the program, "Change username", the exploit is able to accomplish this task by sending a payload designed to overwrite the buffer and the username below it on the stack. The payload is comprised of a buffer fill consisting of 24 'A' characters, and the Root ID, 1337, in hexadecimal format (b'\x00\x00\x00\x00\x39\x05\x00'). After overwriting the user ID, the exploit selects option 3 to initiate a debug shell. This action prompts the program to process the payload, leading to privilege escalation. After successful execution, the script enters an interactive session, allowing the user to interact with the compromised program and obtain the flag.
	

## Lab 3-3

	Lab 3-3 Files:

		3-3_lab.bin:				binary file for lab 3-3
		3-3_exploit.py:				python script used to exploit Lab 3-3
		3-3_flag.png:				screenshot of successful script execution (in DEBUG mode) and flag retrieval


   The exploit for Lab 3-3 builds on the concept from lab 3-1, with a main objective to bypass a stack canary. However, unlike Lab 3-1, where memory leaks were exploitable, and Lab 3-2, which provided variables to manipulate on the stack, Lab 3-3 operates within a different context. The target program here manages network connections, utilizing a child-forking approach for each new connection and terminates upon any detection of stack crashing.  Due the absence of memory leaks or stack variable exploits, the script adopts a brute-force approach.
	
   Step 1 of the exploit involves brute-forcing the stack cookie. This is accomplished through two nested loops: one for iterating through each byte of the cookie and the other to test all possible byte values (0x00 to 0xFF). It is important to note that each loop iteration requires a new connection to the target as an incorrect guess leads to the child process being terminated. However, since the program permits the spawning of an unlimited number of child processes and each child inherits the parents cookie value, the process can be repeated as many times as necessary.
	
   Starting with the first byte, the script cycles through all possible byte values from 0x00 to 0xFF. For each iteration, it constructs a payload with a buffer fill of 24 'A' characters, any previously discovered bytes of the cookie, and the current byte guess. The exploit then waits a predetermined amount of time for a response from the server - specifically for the confirmation message "You may pass" that signifies the correct cookie guess. Upon a correct guess, 	the script proceeds to append the newly discovered byte to the maintained cookie values and progresses to the next byte. Alternatively, if the server remains silent or detects stack corruption, causing an EOFError and connection termination, the script moves to the next guess for the current byte. A connection is re-established and the process repeats until all cookie bytes are identified.

   When the cookie is complete, the script proceeds to the final step where it prepares and sends a unique payload. The payload is comprised of a buffer fill consisting of 24 'A' characters, the discovered cookie value, 8 'B' characters to fill the rbp stack value, the address necessary for executing the specified opcode (leveraging 0xffe4 to represent 'JMP RSP'), and followed finally by the shellcode. Once the payload is sent, the script enters an interactive session, allowing the user to interact with the compromised program and obtain the flag.

	
## Additional Notes

   - Each file is named in the format: "3-X_Title," where "X" corresponds to the lab number, and "Title" describes the file's purpose or content.
	
   - All python scripts require Python 3, pwntools
      > sudo apt-get install python3 <br>
      > pip install pwntools <br>
      - installation instructions assume Linux-based systems
		
   - scripts can be executed using the format `python3 programName`. 
      > python3 3-2_script.py

   - Notes for Lab 3-3: 
	
      - The script does not include functionality to detect the hex value 0x0a as it represents a newline character, and I could not determine how distinguishing the raw hex value, 0x0a, from a newline character during processing. If the script exits without finding a specific byte, it means the byte was 0x0a. In such cases, you should run the program again as a new cookie will be generated.
		
      - There is a DEBUG constant in the script which is set to False by default. If you want to monitor the process step-by-step, it is advisable to turn on DEBUG by setting it to True.
		
      - Due to space constraints, a significant portion of the 3-3 output screenshot has been omitted for readability. Only the top and bottom sections of the output are displayed.
