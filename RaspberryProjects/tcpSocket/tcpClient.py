import socket

HOST = '192.168.43.36' # Enter IP or Hostname of your server
PORT = 1111 # Pick an open Port (1000+ recommended), must match the server port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))


reply = s.recv(1024)
print(reply)
while True:
    command = input('Enter your command: ')
    string_encoded = command.encode()
    s.send(string_encoded)
    if (command == 'quit'):
        print("terminate")
        break
    # print(reply)