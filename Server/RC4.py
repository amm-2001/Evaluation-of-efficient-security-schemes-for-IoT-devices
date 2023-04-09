import socket
from Cryptodome.Cipher import ARC4


HOST = 'Server IP Address'
PORT = 8090 # The Port number default 8090

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)
print("Listening for incoming connections on IP:", HOST, "and port:", PORT)

key = b'Key in Bytes'
byte_data = []
client, addr = s.accept()
while True:
    content = client.recv(4096)

    if len(content) == 0:
        break
    else:
        totalContent = content #totalcontent is the encrypted message and it's type is Bytes
print(f"encrypted message: {totalContent}")
decipher = ARC4.new(key)
print("Closing connection")
msg = decipher.decrypt(totalContent)
for c in msg:
    byte_data.append(c)
client.close()
strings = "".join(map(chr, byte_data)) #Change the type from Bytes to String
print(f"Message After decryption: {strings}")