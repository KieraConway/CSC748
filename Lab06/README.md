# CSC 748 - Software Exploitation
## Lab 06 Assignments

**Student Name:** Kiera Conway
**Due Date:** October 22, 2023

This folder contains lab files and scripts for the lab 06 Uninitialized Variable/Function challenges

## Lab 6-1
	
 	Lab 6-1 Files:

		6-1_lab.bin:		binary file for lab 6-1
		6-1_exploit.py:		python script used to exploit Lab 6-1
		6-1_flag.png:		screenshot of successful script execution and flag retrieval
  
   ### Target Program:
   The target program for lab 6-1 creates a scenario where a user must correctly identify and set a username and authentication code to gain access to the system. This process is facilitated through a menu format presenting various options including (1) entering a username, (2) confirming the username, and (3) finalizing the login process. This mimics a basic authentication process with a primary goal to either grant or deny access, based on the correctness of the values entered.
	
   This authentication code is randomly generated each time the program is executed through a process involving the generation of a random number, which is then modified by adding 123 and taking the result modulo 1000. This final authentication code is the 4 digit pin required to gain shell access. 
	
   ### Vulnerability:
   A vulnerability is exposed relating to the uninitialized variable `tmp[]`, which is used to temporarily store the username input by the user. This is dangerous as the final pin required for authentication shares the same stack location as this variable. Since the program fails to overwrite this stack space, if the user selects "Confirm username" (Option 2) before setting a username (Option 1), the program will leak the private pin unintentionally, assuming it's printing the username.

   ### Exploit:
   The exploit for this lab involves connecting to a remote server and interacting with the binary program. Through this interaction, the exploit targets an Uninitialized Variable vulnerability within the `configure_username()` function. The primary goal of this exploit is toinvoke a shell by leveraging the leaked authentication code and username, ultimately enabling the successful execution of a login procedure.
	
   The exploitation process begins by selecting Option 2: "Confirm username" to reveal the authentication code that remains on the stack. The sequence of code execution enables this exploit as the random pin calculation and storage occur before the target program validates the existence of a valid username. Therefore, since the "Confirm username" operation fails to initialize the `tmp[]` variable, the authentication code remains intact on the stack if no username has been entered yet. As such, by confirming the username prior to setting it, the script is able to extract the authentication code directly from the stack's memory.

   The script proceeds by looping back to the main menu and selecting  Option 1: "Enter username," where it inputs 'admin.' This choice was identified as the target username during the pre-exploit disassembly analysis phase conducted in GDB. The script then triggers Option 3 to conclude the login process, where it delivers the leaked authentication code as a decimal integer encoded as bytes. Upon successful execution of this procedure, the script transitions into an interactive session, granting the user the ability to interact with the compromised program and obtain the flag.



## Lab 6-2
		
	Lab 6-2 Files:

		6-2_lab.bin:		binary file for lab 6-2
		6-2_exploit.py:		python script used to exploit Lab 6-2
		6-2_flag.png:		screenshot of successful script execution and flag retrieval
		
   ### Target Program:
   The target program for Lab 6-2 is an application that combines mathematical operations and message handling in a menu-driven interface. This program allows users to create mathematical equations, add numbers to those equations, choose mathematical operations (addition, subtraction, multiplication, or division), and solve the equations. Additionally, it provides options for drafting, viewing, and deleting messages. The program aims to demonstrate the functionality of an interactive menu and the utilization of structures for mathematical operations and message handling.

   ### Vulnerability:
   This program exhibits a vulnerability related to uninitialized heap memory. The program allocates the necessary memory on the heap when users create mathematical equations or draft messages by utilizing the `malloc` function. The issue with this implementation stems from how memory is managed after being allocated and subsequently freed. Instead of clearing or zeroing out the memory, it is marked as unused but remains in its prior state, potentially containing arbitrary data from the previous usage of that memory block. This vulnerability poses a risk as calling malloc with the same size for memory allocation may return a block with residual data from a prior usage.	
	
   ### Exploit:
   The exploit for this lab establishes a connection to a remote server and interacts with the binary, where it then exploits the Uninitialized Heap Memory vulnerability explained above. The primary goal of this exploit is to invoke a shell by manipulating the memory and control flow of the program to execute the `debugshell()` function. 
	
   To exploit this vulnerability, the script executes a sequence of operations within the target program. First, it selects "Draft New Message" (Option 5) from the program's menu, which triggers the first memory allocation on the heap. This step allows the script to fill the heap with a specifically crafted payload consisting of 8 "A"s to fill the buffer, followed by the address `0x401371`, which corresponds to the target `debugshell()` function. The inclusion of this address is crucial as it overwrites overwrites the storage location of the `((math_t *)todo)->op` address. The script then selects "Delete Message" (Option 7) to free the memory without clearing its contents.
	
   The script selects Option 1: 'Create an Equation' next, which calls `malloc()` of the same size to reallocate the same heap of memory. Since this newly allocated memory is of the same size and location, it retains the same data as before, including the target address pointing to `debugshell()`. Therefore, when the final phase of the exploit is executed by selecting "Solve Equation" (Option 4), the script unintentionally executes the target address when it attempts to call the target operation. In normal program execution, the user's chosen math operation address is placed on the heap at `((math_t *)todo)->op` and is called at this stage. However, as the address corresponding to the `((math_t *)todo)->op` variable has been replaced with the address `0x40137`, the program executes the `debugshell()` function instead. Upon successful execution of this procedure, the script transitions into an interactive session, granting the user the ability to interact with the compromised program and obtain the flag. 


## Lab 6-3

	Lab 6-3 Files:

		6-3_lab.bin:		binary file for lab 6-3
		6-3_exploit.py:		python script used to exploit Lab 6-3
		6-3_flag.png:		screenshot of successful script execution and flag retrieval
		
   ### Target Program:
   The target program for Lab 6-3 simulates a basic number analysis tool. It first enters the `login()` function where users are prompted to input a username and password to 'log in'. The input for this prompt is (unimportant?) as the program will always returns a successful authentication status since the program does not perform any actual authentication. Next, the program enters the run() function where the user is prompted to specify the size of a list of numbers (`nums[]`), either "small" or "large." Based on the user's input, the program determines the length (`len`) of the list, either 5 or 10 respectively, and proceeds to accept the input numbers. It then iterates the entire length of the list and calculates the largest and smallest numbers, which it then and displays to the console. 
   
   However, this program exhibits two critical initial vulnerabilities. The first vulnerability stems from an uninitialized variable, `len`, found within the `run()` function. This is dangerous as the buffer used to store the `username[]` input from the prompt in the `login()` function shares the same stack location as this `len` variable. The second vulnerability relates to the absence of a catch-all 'else statement' during the assignment of the `len` variable. In the program, the user is prompted to specify the size of `nums[]`, providing options for "small" or "large." However, if the user's input does not precisely match either of these options, the program fails to overwrite the data present on the stack. Therefore `len` remains uninitialized and any data entered during the username prompt is not overwritten and resides on the stack. This unique configuration allows for the manipulation of the `len` variable, resulting in the ability to assign it a custom value that would otherwise be unattainable. This creates an exploitable scenario that can lead to unauthorized manipulation and control of the program's behavior.
   
   ### Exploit:
   The exploit for this lab establishes a connection to a remote server and interacts with the binary, where it then exploits an uninitialized variable vulnerability within the `run()` function. The primary goal of this exploit is to invoke a shell by leveraging the uninitialized variable `len` extend stack writing and bypass the NX security feature via a ROP chain. 
	
   To exploit this vulnerability, the script begins by injecting a unique payload through the username prompt, where the buffer is filled with 40 'A' bytes, and the `len` variable is set to 25. This initial step exploits the first vulnerability to manipulate the program into believing the stack allocated more space for `nums[]` than actually available. To ensure the `len` value is not overwritten, the target program then exploits the second vulnerability by responding to the "How big is your list of numbers (small, large)?" prompt inside the `run()` function with a placeholder value. Since there's no catch-all 'else' statement, if the input doesn't match either "small" or "large," `len` remains uninitialized and retaines the custom value '25' set in the previous payload. 

   Now that the exploit has the ability to write beyond the allocated stack space for `nums[]`, it proceeds to send a custom payload in a step-by-step fashion. Since the program assumes users are entering values in a list, the payload is sent in 8-byte increments and is divided into four parts:
	
   #### 1) Buffer Fill
   This initial segment is designed to populate the buffer values with incrementing arbitrary values, progressively advancing the payload's position 8-bytes at a time. This section is executed 11 times as a loop to deliver to fill 88 bytes: (80 for `nums[]` + 8 for `input`)
   
   #### 2) Avoid Variable Clobbering
   The primary goal of this second segment is to navigate the stack layout carefully, preventing interference with the `len` and `i` variables while targeting the return address. Since the target program relies on `len` and `i` to manage data stored on the stack during its execution, it's essential not to clobber these values. To achieve this, the script sends a payload that overwrites `len` and `i` without unintentionally altering their contents. Since there have been eleven lines sent by this phase, `i` is overwritten with 11 and len is overwritten with the predefined value of 25. By preseving the integrity of these variables, the program is able to function as intended internally, while our exploit can progress to the target return address.

   #### 3) Buffer Fill	
   In this phase, the buffer values between the `len` variable and the return address are filled with incrementing arbitrary values. This section is executed 3 times as a loop to deliver to fill 24 bytes: (4 for `len` + 4 for `i` + 8 for `smallest` + 8 for `largest`)

   #### 4) Deliver ROP Chain	
   The last component of the payload is dedicated to delivering the Return-Oriented Programming (ROP) chain. This chain is  designed to set up the 'execve()' system call, which is responsible for launching a new process. Since the target program is 64-bit, the ROP chain places arguments such as configuring the 'execve()' filename, syscall number, argv parameter, envp parameter in their appropriate registers, as shown below. 

| syscall |   arg0   | arg1 | arg2 |
|---------|----------|------|------|
|   %rax  |   %rdi   | %rsi | %rdx |
|   0x3b  | /bin/sh/ |   0  |   0  |



   However, since there's no "/bin/sh" string present within the program, the ROP chain artificially places the hex equivalent of the string "/bin/bash/" into the RSI register using a `pop rsi; ret` gadget. This results in the RSI register containing (0x68732f6e69622f). Since the syscall will interpret this value as a memory address, instead of a string, it must be copied to an appropriate memory location where the execve() syscall can access it. This is completed using a  `mov [rdi], rsi` as it copies the contents of the RSI register (the "/bin/bash/" string) to a memory location pointed to by RDI. This ensures that the execve() syscall can correctly locate the file name, even when the required string isn't explicitly present in the program's memory.
		
   The ROP chain then continues on to place the correct values in their corresponding registers, after which it can finally execute the 'execve()' system call. A full overview of this ROP chain is shown below
		
   ##### ROP Chain Format:
   ```		
   -- Set execve() Filename --
   pop rsi; ret:       pointer, loads '/bin/bash/' into RSI register for execve() filename
   "/bin/bash/":       contains hex representation of "/bin/bash/"
   move [rdi], rsi:    pointer, copies filename value in RSI to memory location pointed to by RDI
   
   -- Set execve() Syscall Number --
   pop rax; ret:       pointer, loads '59' (sys_execve) into RAX register for syscall
   sys_execve:         contains syscall number (59) for the sys_execve() syscall (64-bit)
   
   -- Set execve() argv Parameter --
   pop rsi; ret:       pointer, loads '0' into RSI register for execve() argv
   execve_argv:        null value (0) for use as argv parameter in sys_execve()
   
   -- Set execve() envp Parameter --
   pop rdx; ret:       pointer, loads '0' into RDX register for execve() envp
   execve_envp:        null value (0) for use as envp parameter in sys_execve()
      
   -- Execute sys_execve() System Call --
   syscall:            pointer, executes sys_execve() system call utilizing populated registers
   ```

   
   Finally, upon successful execution, the script transitions into an interactive session, granting the user the ability to interact with the compromised program and obtain the flag. 
   	
## Additional Notes

   - Each file is named in the format: "6-X_Title," where "X" corresponds to the lab number, and "Title" describes the file's purpose or content.
	
   - All python scripts require Python 3, pwntools
      > sudo apt-get install python3
      > pip install pwntools
      *installation instructions assume Linux-based systems*
		
   - scripts can be executed using the format `python3 programName`. For example:
      > python3 6-2_script.py