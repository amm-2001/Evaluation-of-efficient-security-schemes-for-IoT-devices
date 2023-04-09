"""
import socket
from Cryptodome.Cipher import AES
HOST = 'Server IP Address'
PORT = 8090 # The Port number default 8090

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)


key = b'Key in Bytes'
byte_data = []
client, addr = s.accept()
byte_data =[]
while True:
    content = client.recv(4096)

    if len(content) == 0:
        break
    else:
        totalContent = content #totalcontent is the encrypted message, and it's type is Bytes
print(f"encrypted message: {totalContent}")
decipher = AES.new(key, AES.MODE_ECB)
print("Closing connection")
msg = decipher.decrypt(totalContent)
for c in msg:
    byte_data.append(c)
client.close()
strings = "".join(map(chr, byte_data)) #Change the type from Bytes to String
print(f"Message After decryption: {strings}")
"""
import socket
from Cryptodome.Cipher import AES

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
        decipher = AES.new(key, AES.MODE_ECB)
        msg = decipher.decrypt(chunk)
        for c in msg:
            byte_data.append(c)
        strings = "".join(map(chr, byte_data))
        client.close()
    print(f"Message after decryption: {strings}")
