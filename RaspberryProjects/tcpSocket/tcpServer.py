from socket import *
from time  import sleep



HOST = ''
PORT = 1112
ADDR = (HOST, PORT)
BUFSIZE = 4096

serv = socket(AF_INET, SOCK_STREAM)

serv.bind((ADDR))
serv.listen(5)
serv = socket(AF_INET, SOCK_STREAM)

serv.bind((ADDR))
serv.listen(5)


print("Waiting for connections...")
# accept the connection
conn, addr = serv.accept()

string = "Connected"
string_encoded = string.encode()
conn.send(string_encoded)
print("...connected!")

while True:

    data = conn.recv(1024)
    print(data)
    sleep(0.5)
    decoded = data.decode('utf-8')
    if (decoded == "quit\n"):
        print("Shutdown")
        conn.close()
        break
    # conn.send(data)

    # decoded = data.decode('utf-8')
    
    # print("Received:")
    # print(decoded)
    # try:
    #     conn.send(data)
    # except BrokenPipeError:
    #     print("Broken pipe")
    # if (decoded == "quit"):
    #     print("Shutdown")
    #     conn.close()
    #     break