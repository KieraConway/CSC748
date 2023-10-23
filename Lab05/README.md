# Lab 05 - ASLR

## Lab 5-1

	Lab 5-1 Files:

		5-1_lab.bin:		binary file for lab 5-1
		5-1_exploit.py:		python script used to exploit Lab 5-1
		5-1_flag.png:		screenshot of successful script execution and flag retrieval

   The exploit for this lab establishes a connection to a remote server and interacts with the binary, where it then exploits an ASLR vulnerability using Method 1: Leak and calculate. The primary goal of this exploit is to invoke a shell by executing the hidden win() function.

   Prior to exploitation, the return address offset is calculated by subtracting the base address from the return address, observed within GDB through the use of vmmap and stack view, resulting in an offset of 0x13c7 (5063 decimal). Similarly, the win() offset is also calculated by subtracting the base address from the win address, obtained using GDB's print command, resulting in an offset of 0x1269 (4713 decimal).
	
   The return address was then leaked by sending an initial payload containing 23 'A' characters to the program, ensuring one less than the buffer size+rbp to prevent overwriting with a newline character (0x0a). This payload triggered a buffer overflow in the program, causing the return address to be exposed in the stdout output when the program executed the line "PONG: %s\n". This return address was presented in the format [BufferFill]\n[ReturnAddress]. To precisely locate the return address within this output, the pattern "AAAA\n" was employed as a marker to indicate the location of the return address. The script utilized this marker to remove the 'A' characters from the output and subsequently extract and convert the remaining data, obtaining the actual return address.

   With PIE enabled, signifying the binary's position-independence and lack of a fixed base address, the return offset is subtracted from the leaked return address to derive the base address dynamically for each execution. This calculated base address is then added to win() offset to obtain the win address, which is used to construct a subsequent payload. This second payload consists of 24 'A' characters, the calculated win() address, and a newline character. The inclusion of 24 'A' characters, as opposed to 23, ensures complete buffer and rbp coverage, facilitating access to the return address.

   Then, to activate the modified return address, the script sends an empty newline to initiate exit of the while loop. After successful execution, the script enters an interactive session, allowing the user to interact with the compromised program and obtain the flag.



## Lab 5-2

	Lab 5-2 Files:
	
		5-2_lab.bin:				binary file for lab 5-2
		5-2_exploit.py:				python script used to exploit lab 5-2
		5-2_flag.png:				screenshot of successful script execution and flag retrieval

   The exploit for this lab establishes a connection to a remote server and interacts with the binary, where it then exploits an ASLR vulnerability using Method 2: Partial Overwrite. The primary goal of this exploit is to invoke a shell by executing the hidden win() function.

   Prior to exploitation, the return address on the stack during execution of greet() is determined by using the objdump command, which shows that when the greet() function starts executing the CPU pushes a return address with offset 0x13c4 (5060 decimal) onto the stack. Similarly, the win() offset is also observed using objdump, showing an offset of 0x13cb (5067 decimal). By comparing these two offsets, we can see that they are very similar and the return address can be changed to the win() address by chaging the LSB C4 to CB.
   
   With this information, the payload can be executed to overwrite the LSB of the return address. The payload consists of 24 'A' characters followed by the target byte. The inclusion of 24 'A' characters, as opposed to 23, ensures complete buffer and rbp coverage, facilitating access to the return address. Once the payload is sent, it causes a buffer overflow in the program, resulting in partial overwrite of the return address on the stack with the byte 0xcb. The program continues execution, and when it attempts to return from the vulnerable function, it unintentionally jumps to win() due to the modified return address. After successful execution, the script enters an interactive session, allowing the user to interact with the compromised program and obtain the flag.


## Lab 5-3

	Lab 5-3 Files:

		5-3_lab.bin:				binary file for lab 5-3
		5-3_exploit.py:				python script used to exploit Lab 5-3
		5-3_flag.png:				screenshot of successful script execution and flag retrieval

   The exploit for this lab establishes a connection to a remote server and interacts with the binary, where it then exploits an ASLR vulnerability using Method 3: Heap-Spraying Attack. The primary goal of this exploit is to invoke a shell by manipulating the binary's heap memory. This process involves deploying NOPs (No-Operation instructions) and a unique shellcode, through which the binary's execution flow is manipulated to gain control over the target system. 	
	
   The first step involves the allocation of heap memory within the target binary. To achieve this, the script crafts a NOP sled  with a predetermined length (32MB in this case) using the Shellcraft library. The script also generates a shellcode using Shellcraft, which is then combined with the NOP sled to create an NOP Payload. The NOP sled serves as a designated landing spot for the program's execution. Instead of a direct jump to a specific function (e.g., 'win'), the program effectively 'slides' along the NOPs until it encounters and executes the shellcode.
	
   Once the NOP payload is crafted and delivered, the script redirects the program's execution flow to the established NOP sled. This is accomplished by transmitting a unique payload designed to overflow the buffer and overwrite the return address. This payload consists of 32 'A' bytes followed by a carefully estimated target address; This address was calculated by simulating the exploit in a controlled environment and identifying an address that consistently fell within the NOP sled.
	
   The program proceeds with its execution, and when it attempts to return from parsing user input within the 'search()' function, it is redirected to the NOP sled due to the modified return address. In the event of a successful execution, the script enters an interactive session, allowing the user to interact with the compromised program and obtain the flag.	
	
	

	
## Additional Notes

   - Each file is named in the format: "5-X_Title," where "X" corresponds to the lab number, and "Title" describes the file's purpose or content.
   
   - All python scripts require Python 3, pwntools
      > sudo apt-get install python3 <br>
      > pip install pwntools <br>
      - installation instructions assume Linux-based systems
		
   - scripts can be executed using the format `python3 programName`. 
      > python3 5-2_script.py

   - Notes for Lab 5-3: 
	
      - This exploit may not always succeed with 100% certainty as the return address is a predefined estimation. If the script crashes without establishing a reverse shell, it indicates that the estimated return address was outside the NOP sled range. In such instances, you should consider re-running the script, as new addresses will be dynamically allocated.
	
      - To enhance the success rate of the exploit, the number of bytes covered by the NOP sled may be increased by modifying the 'SLED_LENGTH' variable. Please be mindful that as 'SLED_LENGTH' increases, both the success rate and execution time will also proportionally increase.

      - In the context of this script, debugging with the standard command `p = gdb.debug("./5-3_lab.bin")` may lead to a signal trap within the `__ctype_init()` function. To work around this issue, an alternative method has been employed for local debugging by attaching GDB to the running process using the following commands:
         > p = process("./5-3_lab.bin") <br>
         > gdb.attach(p)  # Attach GDB to the running process<br>
      - *It is important that these two lines are executed together to ensure a seamless debugging experience and prevent potential errors. This adjustment enables effective local debugging without encountering the signal trap issue observed when using the standard gdb.debug() method.*
