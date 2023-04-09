import socket
import camellia
"""
HOST = 'Server IP Address'
PORT = 8090
key = b'Key in Bytes'

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)

while True:
    print("Waiting for connection...")
    client, addr = s.accept()
    print(f"Connected to {addr}")
    byte_data = []
    b_data = []
    while True:
        content = client.recv(4096)

        if len(content) == 0:
            break
        else:
            b_data += content
            totalContent = bytes(b_data)

    print(f"encrypted message: {totalContent}")

    #c1 = camellia.CamelliaCipher(key=key, mode=camellia.MODE_ECB)
    chunks = [totalContent[i:i + 16] for i in range(0, len(totalContent), 16)]
    for chunk in chunks:
        c1 = camellia.CamelliaCipher(key=key, mode=camellia.MODE_ECB)
        decrypted = c1.decrypt(chunk)
    for c in decrypted:
        byte_data.append(c)
    strings = "".join(map(chr, byte_data)) #Change the type from Bytes to String
    print(f"Message After decryption: {strings}")
client.close()
"""
HOST = 'Server IP Address'
PORT = 8090
key = b'Key in Bytes'

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
while True:
    print("Waiting for connection...")
    client, addr = s.accept()
    print(f"Connected to {addr}")
    byte_data = []
    b_data = []
    while True:
        content = client.recv(4096)
        if len(content) == 0:
            break
        else:
            b_data += content
    totalContent = bytes(b_data)
    print(f"Encrypted message: {totalContent}")
    chunks = [totalContent[i:i + 16] for i in range(0, len(totalContent), 16)]
    for chunk in chunks:
        c1 = camellia.CamelliaCipher(key=key, mode=camellia.MODE_ECB)
        decrypted = c1.decrypt(chunk)
        for c in decrypted:
            byte_data.append(c)
        strings = "".join(map(chr, byte_data))
        print(f"Message after decryption: {strings}")
        client.close()
        print(chunk)