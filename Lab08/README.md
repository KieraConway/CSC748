# Lab 08  - Heap (Part 1)

## Lab 8-1
	
 	Lab 8-1 Files:

		8-1_lab.bin:		binary file for lab 8-1
		8-1_exploit.py:		python script used to exploit Lab 8-1
		8-1_flag.png:		screenshot of successful script execution and flag retrieval


	The target program for Lab 8-1 simulates an archery range where players can shoot arrows at a target. The program initializes a target structure with a hit function, a bow structure, and an arrow structure. Players can choose an arrow type, and the program executes the hit function, which currently always hits the bullseye. The vulnerability in the program lies in the do_archery function, where it dynamically allocates memory for the target, bow, and arrow structures without proper bounds checking. This allows an attacker to overflow the allocated chunks and manipulate the heap layout.
	
	The vulnerability exploited in this scenario is 'Heap grooming (feng shui),' where the attacker carefully arranges the heap to achieve a desirable layout for a controlled overflow that leads to arbitrary code execution. Although the program mallocs the structures in the order Target->Bow->Arrow, the opposite direction is needed to perform a heap overflow. To exploit this vulnerability, 8-1_exploit.py sends player names to the program, creating chunks of different sizes on the heap. The first player name allocates 0x50 to match the size of the Arrow struct and the second player name allocates 0x30 to match the size of the Target struct.	By using the heap to allocate structures of the size Arrow and Target, the heap pulls them from the cache in this order. This arranges the structures appropriately for the overflow. When prompted for the arrow type, the script executes a buffer overflow to overwrite the address in 'hit_action' with the address of the debug_shell function. Then, when the program invokes the hit function, the program jumps to debug_shell, granting the attacker a shell with escalated privileges. Upon successful execution of this procedure, the script transitions into an interactive session, granting the user the ability to interact with the compromised program and obtain the flag.
	



## Lab 8-2
	
 	Lab 8-2 Files:

		8-2_lab.bin:		binary file for lab 8-2
		8-2_exploit.py:		python script used to exploit Lab 8-2
		8-2_flag.png:		screenshot of successful script execution and flag retrieval

	
	The target program for Lab 8-2 is a simple note-taking app that allows users to create, view, edit, and delete notes. The program maintains an array of note pointers and dynamically allocates memory for each note's content. The vulnerability lies in the program's logic, as it lacks proper checks when performing note-related operations. Specifically, the program fails to handle cases where notes are attempted to be edited after they are deleted. This creates a Use-after-Free (UaF) vulnerability, which allows for T-cache poisoning and unintended access to other parts of memory.
	
	The 8-2_exploit.py script takes advantage of this vulnerability to achieve unauthorized access. It strategically allocates and frees chunks on the heap to manipulate the order of notes and create a situation where freed memory is later accessed. Initially, it allocates two chunks, a and b, and then proceeds to free both chunks. The script tricks the program into allowing the user to edit a note that has already been freed. With no protections in place, it	is able to exploit the UaF vulnerability and overwrite b's next pointer. This manipulation of the heap layout enables the script to overwrite the pointer with the address to the username string. Then, when the the script reallocates a chunk of the same size, it leverages malloc() to return this target address. Then, when the user is prompted to add contents to the new allocation, they can instead overwrite the user from 'guest' to 'admin.' With elevated privelieges, the script can now access the debug shell and print the obtained flag.

## Additional Notes

   - Each file is named in the format: "8-X_Title," where "X" corresponds to the lab number, and "Title" describes the file's purpose or content.
	
   - All python scripts require Python 3, pwntools
      > sudo apt-get install python3 <br>
      > pip install pwntools <br>
      *installation instructions assume Linux-based systems*
	
   - scripts can be executed using the format `python3 programName`. 
      > python3 8-2_script.py
