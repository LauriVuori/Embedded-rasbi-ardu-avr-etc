import socket
from time import sleep

HOST = '192.168.0.101'
PORT = 1112
socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket.connect((HOST, PORT))

# Get message from host
print("Waiting message from host...")
reply = socket.recv(1024)
reply = reply.decode('utf-8')
print(reply)

while True:
    command = input('Enter your command: ')
    string_encoded = command.encode()
    socket.send(string_encoded)
    sleep(1)
    if (command == "quit"):
        print("Shutdown")
        break