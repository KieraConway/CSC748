
080494f0 <fatal>:
 80494f0:	f3 0f 1e fb          	endbr32 
 80494f4:	55                   	push   ebp
 80494f5:	89 e5                	mov    ebp,esp
 80494f7:	53                   	push   ebx
 80494f8:	e8 73 fe ff ff       	call   8049370 <__x86.get_pc_thunk.bx>
 80494fd:	81 c3 03 2b 00 00    	add    ebx,0x2b03
 8049503:	8b 83 f0 ff ff ff    	mov    eax,DWORD PTR [ebx-0x10]
 8049509:	8b 00                	mov    eax,DWORD PTR [eax]
 804950b:	ff 75 08             	push   DWORD PTR [ebp+0x8]
 804950e:	8d 93 15 e0 ff ff    	lea    edx,[ebx-0x1feb]
 8049514:	52                   	push   edx
 8049515:	50                   	push   eax
 8049516:	e8 75 fd ff ff       	call   8049290 <fprintf@plt>
 804951b:	83 c4 0c             	add    esp,0xc
 804951e:	ff 75 0c             	push   DWORD PTR [ebp+0xc]
 8049521:	e8 0a fd ff ff       	call   8049230 <perror@plt>
 8049526:	83 c4 04             	add    esp,0x4
 8049529:	6a 01                	push   0x1
 804952b:	e8 30 fd ff ff       	call   8049260 <exit@plt>

08049530 <main>:
	
	#Setup
 
 	register char *sp;
	
	char line[512];
	//    struct sockaddr sin;
	int i, p[2], pid, status;
	FILE *fp;
	char *av[4];
 
	 8049530:	f3 0f 1e fb          	endbr32 
	 8049534:	55                   	push   ebp
	 8049535:	89 e5                	mov    ebp,esp
	 8049537:	56                   	push   esi
	 8049538:	53                   	push   ebx
	 8049539:	81 ec 28 02 00 00    	sub    esp,0x228
	 804953f:	e8 2c fe ff ff       	call   8049370 <__x86.get_pc_thunk.bx>
	 8049544:	81 c3 bc 2a 00 00    	add    ebx,0x2abc
	 
 
	init();
	 804954a:	e8 10 ff ff ff       	call   804945f <init>					
 
 
	#Get input 
	line[0] = '\0';		//init first char of line buffer to the null
	gets(line);			//read line from the standard input
	sp = line;			//pointer to beginning of line buffer
	av[0] = "finger";	//Init first element of the av with string "finger" - This is command that will be executed in child process, subsequent elements are arguments passed to this command
	i = 1;				//index in the av array where new args are added (starts at 1 because the 0th index is already assigned  to "finger"
			
	 804954f:	c6 85 ec fd ff ff 00 	mov    BYTE PTR [ebp-0x214],0x0			# line[0] = '\0';
	 8049556:	8d 85 ec fd ff ff    	lea    eax,[ebp-0x214]
	 804955c:	50                   	push   eax
	 804955d:	e8 5e fc ff ff       	call   80491c0 <gets@plt>				# gets(line);
	 8049562:	83 c4 04             	add    esp,0x4
	 8049565:	8d b5 ec fd ff ff    	lea    esi,[ebp-0x214]
	 804956b:	8d 83 1a e0 ff ff    	lea    eax,[ebx-0x1fe6]					# sp = line;	
	 8049571:	89 85 d0 fd ff ff    	mov    DWORD PTR [ebp-0x230],eax		# av[0] = "finger";
	 8049577:	c7 45 f4 01 00 00 00 	mov    DWORD PTR [ebp-0xc],0x1			# i = 1;



	#while loop
 
	// // // // // // // // // // // // // //
	//parse input stored in the line buffer 
	//to construct an argument vector (av) 
	//for the "finger" command.
	// // // // // // // // // // // // // //
	while (1) {						//  iterate over input characters

	0x804957e <main+78>:	eb 03                	jmp    8049583 <main+0x53>
 
 
		/*Skip Whitespace*/
		while (isspace(*sp)){	
			sp++;					// skip any leading whitespace characters
			 0x8049580 <main+80>:	83 c6 01             	add    esi,0x1							#Skipped on first iteration, ncrements the esi register by 1, moves to next character in the input string.		
			 0x8049583 <main+83>:	e8 88 fd ff ff       	call   0x8049310 <__ctype_b_loc@plt>
			 0x8049588 <main+88>:	8b 00                	mov    eax,DWORD PTR [eax]
			 0x804958a <main+90>:	0f b6 16             	movzx  edx,BYTE PTR [esi]				# moves byte value from the memory location pointed to by esi into EDX. (esi is pointing to the current character in the input string)
			 0x804958d <main+93>:	0f be d2             	movsx  edx,dl
			 0x8049590 <main+96>:	01 d2                	add    edx,edx
			 0x8049592 <main+98>:	01 d0                	add    eax,edx
			 0x8049594 <main+100>:	0f b7 00             	movzx  eax,WORD PTR [eax]
			 0x8049597 <main+103>:	0f b7 c0             	movzx  eax,ax
			 0x804959a <main+106>:	25 00 20 00 00       	and    eax,0x2000
			 0x804959f <main+111>:	85 c0                	test   eax,eax
			 0x80495a1 <main+113>:	75 dd                	jne    0x8049580 <main+0x50>			# goes back to 8049580 if the zero flag is not set, meaning that the current character is a whitespace character.
	
		}
		 
 
 
		/*Check for End of Input*/			
		if (!*sp){
			break;					//If current char is null terminator ('\0') (end of string), break		
			
			 0x80495a3 <main+115>:	0f b6 06             	movzx  eax,BYTE PTR [esi]				# moves byte value from the memory location pointed to by esi into EAX. (esi is pointing to the current character in the input string)
			 0x80495a6 <main+118>:	84 c0                	test   al,al
			 0x80495a8 <main+120>:	0f 84 a3 00 00 00    	je     0x8049651 <main+289>				# jumps to 0x8049651 <main+0x121> if the zero flag is set (byte at current position pointed to by sp is zero (end of input))
	 
		}
 
 
		/*Handle "/W" or "/w" Option*/			
		if (*sp == '/' && (sp[1] == 'W' || sp[1] == 'w')) {				
			
		 0x80495ae <main+126>:	0f b6 06             	movzx  eax,BYTE PTR [esi]			# moves byte value from the memory location pointed to by esi into EAX. (esi is pointing to the current character in the input string), zero-extends it to a 32-bit value.
		 0x80495b1 <main+129>:	3c 2f                	cmp    al,0x2f						# checks if the current character is '/'
		 0x80495b3 <main+131>:	75 2d                	jne    0x80495e2 <main+0xb2>			# jumps to address 0x80495e2 <main+0xb2> if current character is not '/'). If it's not '/', it skips the code block related to handling the "/W" or "/w" option.
		
		 0x80495b5 <main+133>:	8d 46 01             	lea    eax,[esi+0x1]
		 0x80495b8 <main+136>:	0f b6 00             	movzx  eax,BYTE PTR [eax]
		 0x80495bb <main+139>:	3c 57                	cmp    al,0x57						# checks if the current character is 'W'
		 80495bd:	74 0a                	je     80495c9 <main+0x99>			# jumps to the address 0x80495c9 <main+0x99> if the current character is 'W'
		 80495bf:	8d 46 01             	lea    eax,[esi+0x1]
		 80495c2:	0f b6 00             	movzx  eax,BYTE PTR [eax]
		 80495c5:	3c 77                	cmp    al,0x77						# checks if the current character is 'w'
		 80495c7:	75 19                	jne    80495e2 <main+0xb2>			# jumps to 0x80495e2 <main+0xb2> if the current character is not 'w'). If it's not 'w', it skips the code block related to handling the "/W" or "/w" option.	


			sp += 2;			//increments sp by 2 and 
			av[i++] = "-l";		//assign the "-l" to the av array at index i
			
			 80495c9:	83 c6 02             	add    esi,0x2
			 80495cc:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
			 80495cf:	8d 50 01             	lea    edx,[eax+0x1]
			 80495d2:	89 55 f4             	mov    DWORD PTR [ebp-0xc],edx
			 80495d5:	8d 93 21 e0 ff ff    	lea    edx,[ebx-0x1fdf]
			 80495db:	89 94 85 d0 fd ff ff 	mov    DWORD PTR [ebp+eax*4-0x230],edx		#stores value in edx into the memory location calculated by the expression [ebp+eax*4-0x230]
	 
		}
		
		
		
		/*Handling Non-Whitespace Characters*/				
		if (*sp && !isspace(*sp)) {						//If current char is not whitespace and not null...
					
		 0x80495e2 <main+178>:	0f b6 06             	movzx  eax,BYTE PTR [esi]			# moves byte value from the memory location pointed to by esi into EAX. (esi is pointing to the current character in the input string), zero-extends it to a 32-bit value.
		 0x80495e5 <main+181>:	84 c0                	test   al,al						# It checks if the byte loaded in the previous instruction is zero.
		 0x80495e7 <main+183>:	74 9a                	je     8049583 <main+0x53>			# jumps to 0x8049583 <main+0x53> if previous comparison was equal (if the current character is the null terminator). This effectively ends the loop.
		 0x80495e9 <main+185>:	e8 22 fd ff ff       	call   8049310 <__ctype_b_loc@plt>	# Calls character classification function isspace(*sp)
		 0x80495ee <main+190>:	8b 00                	mov    eax,DWORD PTR [eax]
		 0x80495f0 <main+192>:	0f b6 16             	movzx  edx,BYTE PTR [esi]
		 0x80495f3 <main+195> :	0f be d2             	movsx  edx,dl


			av[i++] = sp;								//Assign current position (sp) to av[i++] (indicates start of a new argument in the argument vector)					
			
			 0x80495f6 <main+198>:	01 d2                	add    edx,edx
			 0x80495f8 <main+200>:	01 d0                	add    eax,edx
			 0x80495fa <main+202>:	0f b7 00             	movzx  eax,WORD PTR [eax]
			 0x80495fd <main+205>:	0f b7 c0             	movzx  eax,ax
			 0x8049600 <main+208>:	25 00 20 00 00       	and    eax,0x2000
			 0x8049605 <main+213>:	85 c0                	test   eax,eax
			 0x8049607 <main+215>:	0f 85 76 ff ff ff    	jne    8049583 <main+0x53>			# jumps to the address 0x8049583 <main+83> if previous comparison was not equal (was a whitespace character), it ends the loop 	
			 
			 0x804960d <main+221>:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]		#incrementing counter ebp-0xc
			 0x8049610 <main+224>:	8d 50 01             	lea    edx,[eax+0x1]
			 0x8049613 <main+227>:	89 55 f4             	mov    DWORD PTR [ebp-0xc],edx
			 
			 0x8049616 <main+230>:	89 b4 85 d0 fd ff ff 	mov    DWORD PTR [ebp+eax*4-0x230],esi
			 0x804961d <main+237>:	eb 03                	jmp    8049622 <main+0xf2>			 
			 
			/* traverse characters */ 
			while (*sp && !isspace(*sp)){		//traverse until a whitespace char or null terminator is encountered	
			  sp++;
				 0x804961f <main+239>:	83 c6 01             	add    esi,0x1
				 0x8049622 <main+242>:	0f b6 06             	movzx  eax,BYTE PTR [esi]
				 0x8049625 <main+245>:	84 c0                	test   al,al
				 0x8049627 <main+247>:	74 20                	je     0x8049649 <main+0x119>			# jumps to address 0x8049649 <main+281> if the current character is the null terminator, This ends the loop.
				 0x8049629 <main+249>:	e8 e2 fc ff ff       	call   0x8049310 <__ctype_b_loc@plt>	# Calls character classification function isspace(*sp)
				 0x804962e <main+254>:	8b 00                	mov    eax,DWORD PTR [eax]
				 0x8049630 <main+256>:	0f b6 16             	movzx  edx,BYTE PTR [esi]
				 0x8049633 <main+259>:	0f be d2             	movsx  edx,dl
				 0x8049636 <main+262>:	01 d2                	add    edx,edx
				 0x8049638 <main+264>:	01 d0                	add    eax,edx
				 0x804963a <main+266>:	0f b7 00             	movzx  eax,WORD PTR [eax]
				 0x804963d <main+269>:	0f b7 c0             	movzx  eax,ax
				 0x8049640 <main+272>:	25 00 20 00 00       	and    eax,0x2000
				 0x8049645 <main+277>:	85 c0                	test   eax,eax
				 0x8049647 <main+279>:	74 d6                	je     0x804961f <main+0xef>			# jumps to address 0x804961f <main+239> if previous comparison was equal (if the character is not a whitespace character), continuing the loop to the next iteration 
			}

			/* terminate current argument */
			*sp = '\0';			//encountered whitespace is replaced with a null terminator ('\0')
			 0x8049649 <main+281>:	c6 06 00             	mov    BYTE PTR [esi],0x0			# null-terminates current string, indicating the end of the current argument.
			 0x804964c <main+284>:	e9 32 ff ff ff       	jmp    8049583 <main+0x53>			# jump back to the beginning of the outer loop
			 0x8049651 <main+289>:	90                   	nop
		} 

	}
	
	av[i] = 0;	//mark the end of the argument vector (av) to indicate end of arguments for command
	  
     0x8049652 <main+290>:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]				#get value of i from ebp-0xc (i marks end of args)
     0x8049655 <main+293>:	c7 84 85 d0 fd ff ff 	mov    DWORD PTR [ebp+eax*4-0x230],0x0		#clears out value on stack under argument(s)
		
	/* Create Pipe */		
		
	// Creates a pipe using the pipe syscall. 
	// If the pipe creation fails (returns a value less than 0), 
	// call fatal function to print error msg and terminate program
	
	//Pipe Notes:
	// pipe is a form of interprocess communication 
	// it allows one proc to send data to another proc
	//
	//it has two ends:
	//	Read End	(p[0]): Where data is read from the pipe (This program - the parent process uses this end to read the output of the "finger" command executed by the child process after forking)
	//	Write End	(p[1]): Where data is written into the pipe(This program - the child process writes its stdout to this end)
	
	//LOCATION of read/write: 0xffffcffc
	
    if (pipe(p) < 0)
        fatal(argv[0], "pipe");

		 0x8049660 <main+304>:	8d 85 e4 fd ff ff    	lea    eax,[ebp-0x21c]						# prepare argument for the pipe function call.
		 0x8049666 <main+310>:	50                   	push   eax									# set argument for pipe()
		 0x8049667 <main+311>:	e8 64 fc ff ff       	call   80492d0 <pipe@plt>					# calls the pipe function.
		 0x804966c <main+316>:	83 c4 04             	add    esp,0x4								# adjust stack pointer to remove argument pushed earlier.
		 0x804966f <main+319>:	85 c0                	test   eax,eax								# tests the result of the pipe function call.
		 0x8049671 <main+321>:	79 15                	jns    8049688 <main+0x158>					# jumps to 0x8049688 if pipe function call is successful
		 
		 0x8049673 <main+323>:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
		 0x8049676 <main+326>:	8b 00                	mov    eax,DWORD PTR [eax]
		 0x8049678 <main+328>:	8d 93 24 e0 ff ff    	lea    edx,[ebx-0x1fdc]
		 0x804967e <main+334>:	52                   	push   edx									# set argument for fatal()
		 0x804967f <main+335>:	50                   	push   eax									# set argument for fatal()
		 0x8049680 <main+336>:	e8 6b fe ff ff       	call   80494f0 <fatal>						# call fatal()

 	/* Fork Child Proc */
    if ((pid = fork()) == 0) {
		close(p[0]);			//Closes read end of the pipe (p[0])
			
		 0x8049685 <main+341> :	83 c4 08             	add    esp,0x8
		 0x8049688 <main+344>:	e8 53 fc ff ff       	call   0x80492e0 <fork@plt>
		 0x804968d <main+349>:	89 45 f0             	mov    DWORD PTR [ebp-0x10],eax
		 0x8049690 <main+352>:	83 7d f0 00          	cmp    DWORD PTR [ebp-0x10],0x0
		 0x8049694 <main+356>:	75 57                	jne    0x80496ed <main+0x1bd>				#if pipe error, jump to close
		 
		 0x8049696 <main+358>:	8b 85 e4 fd ff ff    	mov    eax,DWORD PTR [ebp-0x21c]
		 0x804969c <main+364>:	50                   	push   eax
		 0x804969d <main+365>:	e8 5e fc ff ff       	call   0x8049300 <close@plt>

		 
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
			
			 0x80496a2 <main+370>:	83 c4 04             	add    esp,0x4
			 0x80496a5 <main+373>:	8b 85 e8 fd ff ff    	mov    eax,DWORD PTR [ebp-0x218]
			 0x80496ab <main+379>:	83 f8 01             	cmp    eax,0x1
			 0x80496ae <main+382>:	74 20                	je     0x80496d0 <main+0x1a0>
			 
			 0x80496b0 <main+384>:	8b 85 e8 fd ff ff    	mov    eax,DWORD PTR [ebp-0x218]
			 0x80496b6 <main+390>:	6a 01                	push   0x1
			 0x80496b8 <main+392>:	50                   	push   eax
			 0x80496b9 <main+393>:	e8 f2 fa ff ff       	call   80491b0 <dup2@plt>				# dup2(p[1] = 4, 1)


			close(p[1]);	//original fd p[1] is closed (duplicate remains open)
			 80496be:	83 c4 08             	add    esp,0x8
			 80496c1:	8b 85 e8 fd ff ff    	mov    eax,DWORD PTR [ebp-0x218]
			 80496c7:	50                   	push   eax
			 80496c8:	e8 33 fc ff ff       	call   8049300 <close@plt>


        }
		
		/* Execute Finger */
		execv("/usr/bin/finger", av);		//"finger" command is executed with the provided argument vector (av) using execv.
		/*
		execv@plt (
		   [sp + 0x0] = 0x0804a029 → "/usr/bin/finger",
		   [sp + 0x4] = 0xffffcfe8 → 0x0804a01a → "finger",
		   [sp + 0x8] = 0x0804a01a → "finger"
		)
		*/
		 0x80496cd <main+413>:	83 c4 04             	add    esp,0x4
		 0x80496d0 <main+416>:	8d 85 d0 fd ff ff    	lea    eax,[ebp-0x230]		# ebp = 0xffffd218-0x230 = 0xFFFFCFE8 = "finger"
		 0x80496d6 <main+422>:	50                   	push   eax
		 0x80496d7 <main+423>:	8d 83 29 e0 ff ff    	lea    eax,[ebx-0x1fd7]		# ebx = 0x804c000-0x1fd7 = 0x0804A029 =  "/usr/bin/finger"
		 0x80496dd <main+429>:	50                   	push   eax
		 0x80496de <main+430>:	e8 bd fb ff ff       	call   80492a0 <execv@plt>
		 
		_exit(1);							//If execv fails, child proc will exit

		 0x80496e3:	83 c4 08             	add    esp,0x8
		 0x80496e6:	6a 01                	push   0x1
		 0x80496e8:	e8 e3 fa ff ff       	call   80491d0 <_exit@plt>
		 
    }

	 
	if (pid == -1){							//parent: checks if forking of child failed (returns -1)
		fatal(argv[0], "fork");				//If true, call fatal function to print error msg and terminate program

		
		 0x80496ed:	83 7d f0 ff          	cmp    DWORD PTR [ebp-0x10],0xffffffff
		 80496f1:	75 15                	jne    8049708 <main+0x1d8>
		 80496f3:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
		 80496f6:	8b 00                	mov    eax,DWORD PTR [eax]
		 80496f8:	8d 93 39 e0 ff ff    	lea    edx,[ebx-0x1fc7]
		 80496fe:	52                   	push   edx
		 80496ff:	50                   	push   eax
		 8049700:	e8 eb fd ff ff       	call   80494f0 <fatal>

    }	 
	 
	 
	close(p[1]);							//parent: close write end of the pipe (p[1]), as it's not needed for writing in parent

	 8049705:	83 c4 08             	add    esp,0x8
	 8049708:	8b 85 e8 fd ff ff    	mov    eax,DWORD PTR [ebp-0x218]
	 804970e:	50                   	push   eax
	 804970f:	e8 ec fb ff ff       	call   8049300 <close@plt>
 
	if ((fp = fdopen(p[0], "r")) == NULL){	//parent: associate read end of pipe (p[0]) with a FILE stream (fp) using fdopen. 
		fatal(argv[0], "fdopen");			//if fails, call fatal function to print error msg and terminate program.
	
	 8049714:	83 c4 04             	add    esp,0x4
	 8049717:	8b 85 e4 fd ff ff    	mov    eax,DWORD PTR [ebp-0x21c]
	 804971d:	8d 93 3e e0 ff ff    	lea    edx,[ebx-0x1fc2]
	 8049723:	52                   	push   edx
	 8049724:	50                   	push   eax
	 8049725:	e8 46 fb ff ff       	call   8049270 <fdopen@plt>
	 804972a:	83 c4 08             	add    esp,0x8
	 804972d:	89 45 ec             	mov    DWORD PTR [ebp-0x14],eax
	 8049730:	83 7d ec 00          	cmp    DWORD PTR [ebp-0x14],0x0
	 8049734:	75 32                	jne    8049768 <main+0x238>
	 8049736:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
	 8049739:	8b 00                	mov    eax,DWORD PTR [eax]
	 804973b:	8d 93 40 e0 ff ff    	lea    edx,[ebx-0x1fc0]
	 8049741:	52                   	push   edx
	 8049742:	50                   	push   eax
	 8049743:	e8 a8 fd ff ff       	call   80494f0 <fatal>
	} 
	
	
	while ((i = getc(fp)) != EOF) {			//parent: read char from fp until EOF is reached
	
		//for each character:
	
		if (i == '\n')			//if char is newline
			putchar('\r');		//print a carriage return ('\r') to simulate a new line.		
			 8049748:	83 c4 08             	add    esp,0x8
			 804974b:	eb 1b                	jmp    8049768 <main+0x238>
			 804974d:	83 7d f4 0a          	cmp    DWORD PTR [ebp-0xc],0xa
			 8049751:	75 0a                	jne    804975d <main+0x22d>
			 8049753:	6a 0d                	push   0xd
			 8049755:	e8 66 fb ff ff       	call   80492c0 <putchar@plt>
		}

		putchar(i);				//print char
		 804975a:	83 c4 04             	add    esp,0x4
		 804975d:	ff 75 f4             	push   DWORD PTR [ebp-0xc]
		 8049760:	e8 5b fb ff ff       	call   80492c0 <putchar@plt>

		 8049765:	83 c4 04             	add    esp,0x4
		 8049768:	ff 75 ec             	push   DWORD PTR [ebp-0x14]
		 804976b:	e8 80 fb ff ff       	call   80492f0 <getc@plt>
		 8049770:	83 c4 04             	add    esp,0x4
		 8049773:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
		 8049776:	83 7d f4 ff          	cmp    DWORD PTR [ebp-0xc],0xffffffff
		 804977a:	75 d1                	jne    804974d <main+0x21d>
	}

	fclose(fp);		//parent: Close fp after reading is complete

	 804977c:	ff 75 ec             	push   DWORD PTR [ebp-0x14]
	 804977f:	e8 5c fa ff ff       	call   80491e0 <fclose@plt>
	 
	while ((i = wait(&status)) != pid && i != -1);	//parent: waits for the child to complete (continues until true)
	 8049784:	83 c4 04             	add    esp,0x4
	 8049787:	90                   	nop
	 8049788:	8d 85 e0 fd ff ff    	lea    eax,[ebp-0x220]
	 804978e:	50                   	push   eax
	 804978f:	e8 8c fa ff ff       	call   8049220 <wait@plt>
	 8049794:	83 c4 04             	add    esp,0x4
	 8049797:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
	 804979a:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
	 804979d:	3b 45 f0             	cmp    eax,DWORD PTR [ebp-0x10]
	 80497a0:	74 06                	je     80497a8 <main+0x278>
	 80497a2:	83 7d f4 ff          	cmp    DWORD PTR [ebp-0xc],0xffffffff
	 80497a6:	75 e0                	jne    8049788 <main+0x258>
	;
	
	return(0);
	 80497a8:	b8 00 00 00 00       	mov    eax,0x0
	 80497ad:	8d 65 f8             	lea    esp,[ebp-0x8]
	 80497b0:	5b                   	pop    ebx
	 80497b1:	5e                   	pop    esi
	 80497b2:	5d                   	pop    ebp
	 80497b3:	c3                   	ret    
	 80497b4:	66 90                	xchg   ax,ax
	 80497b6:	66 90                	xchg   ax,ax
	 80497b8:	66 90                	xchg   ax,ax
	 80497ba:	66 90                	xchg   ax,ax
	 80497bc:	66 90                	xchg   ax,ax
	 80497be:	66 90                	xchg   ax,ax
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