# Lab 06 - Introductory Binary Exploitation

## Lab 1-1
	
	Lab 1-1 Files:

		1-1_lab.bin:		binary file for lab 1-1
		1-1_script.py:		python script used to exploit Lab 1-1
		1-1_SS_flag.png:	screenshot of successful script execution and flag retrieval

   This script establishes a connection to a remote server and interacts with the binary, obtaining a secret string from the server and sending it back to exploit the vulnerability.


## Lab 1-2

	Lab 1-2 Files:
	
		1-2_lab.bin:				binary file for lab 1-2
		1-2_script.py:				python script used to exploit lab 1-2
		1-2_SS_flag.png:			screenshot of successful script execution and flag retrieval
		1-2_SS_identifySymbol.png:		screenshot identifying symbol names and their corresponding addresses

   This script interacts with the binary in two steps. In the first step, it prints all symbol names and their corresponding addresses, which is used to identify the target symbol for the second step. In the second step, the script establishes a connection to a remote server, obtains the symbol address for the target symbol found in step 1 ('win'), exploits the vulnerability by sending the symbol address as a string to the server, and initiates an interactive session.


## Lab 1-3

	Lab 1-3 Files:
	
		1-3_lab.bin:				binary file for lab 1-3
		1-3_script.py:				python script used to exploit Lab 1-3
		1-3_SS_flag.png:			screenshot of successful script execution and flag retrieval
		1-3_SS_identifySymbol.png:		screenshot identifying symbol names and their corresponding addresses

	
   This script interacts with a position-independent binary in two steps. In the first step, it prints all symbol names and their corresponding addresses, which is used to identify the target symbol for the second step. In the second step, the script establishes a connection to a remote server, reads the base address, obtains the symbol address for the target symbol found in step 1 ('win'), and calculates the absolute memory address of the symbol by adding the base address and symbol address together. Since the binary's code and data segments are loaded at random memory addresses each time it's executed, their relative offsets remain constant. As such, the absolute memory address of the 'win' function can be solved for by adding the base address and symbol address together. Once the absolute memory address of the symbol is calculated, the script exploits a vulnerability by sending the it as a string to the server, initiating an interactive session.
	


## Additional Notes

   - Each file is named in the format: "1-X_Title," where "X" corresponds to the lab number, and "Title" describes the file's purpose or content.
	
   - All python scripts require Python 3, pwntools
      > sudo apt-get install python3 <br>
      > pip install pwntools <br>
      *installation instructions assume Linux-based systems*
	
   - scripts can be executed using the format `python3 programName`. 
      > python3 1-2_script.py

  
## Deliverable Question

**A few sentences describing your current knowledge and skill level (if any) with software exploitation. Is this a topic you’ve explored at all before? If so, in what way? If not, totally fine.**

My current knowledge and skill level with software exploitation is at a relatively introductory level. During my undergraduate studies, my exposure to exploitation was mostly theoretical. As a result, while my hands-on exposure has been limited, I have a general understanding of some topics closely related to software exploitation. These included an understanding of firewall configurations, conducting packet sniffing and analysis, analyzing log data, and processing and analyzing memory dumps.

Although most of my courses were theoretical, I did have some limited hands-on experience. I had opportunities to practice scanning web applications for vulnerabilities with Burp Suite and Zed Attack Proxy (ZAP), analyzing network traffic with Wireshark, analyzing binary instructions with IDA, searching for network vulnerabilities with OpenVAS, cracking passwords with John the Ripper and HashCat, and various additional command-line tools.

While I have been introduced to these tools, I have not had many opportunities to apply them in a CTF type environment. I am very excited for this course as it provides a practical platform to test and enhance my foundational knowledge. Although I anticipate a challenge, I look forward to improving my software exploitation skills this semester.
