from __future__ import print_function

''' Script Module Importing '''
# Python Standard Libaries
import sys          # import Python Standard Sys Library
import socket       # import Python Standard Socket Library
import hashlib

PORT = 7033        # Server Port

''' Main Script Starts Here '''

if __name__ == '__main__':

    try:
        clientSocket = socket.socket()          # Create client socket
        local_host = socket.gethostbyname(socket.gethostname()) #use hostname to retrieve IP address 
        #localHost = '127.0.0.1'                 # Standard loopback interface address (local_host)
        print(f'[*] Attempt Connection to {local_host}:{PORT}')
        
        clientSocket.connect((local_host, PORT)) # connect the client
        print("[*] Socket Connected\n")
        
        #exploit goes here
        
        '''
        print("[*] Initiating Close Socket...")
        clientSocket.close()
        print("[*] Client Socket Closed")
        '''

        
        #
        #FOR DEBUGGING, REMOVE WHEN DONE
        #

        # Wait for user input
        try:
            choice = input("[*] Enter '1' to close the socket: ")

            if choice == '1':
                print("[*] Initiating Close Socket...")
                clientSocket.close()
                print("[*] Client Socket Closed")
            else:
                print("[*] Invalid choice, not closing the socket.")

        except KeyboardInterrupt:
            pass  # Handle Ctrl+C gracefully

        print("[*] Script closed.")
        
        #
        #END DEBUGGING
        #
        
    except Exception as err:
        sys.exit(err)    