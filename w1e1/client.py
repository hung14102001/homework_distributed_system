import socket

def send_request(message):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(("127.0.0.1", 5050))
        s.sendall(message.encode("utf-8"))
        response = s.recv(1024).decode("utf-8")
        return response

if __name__ == "__main__":
    print(send_request("KV/1.0 GET\n"))
    print(send_request("KV/1.0 PUT user42 Alice\n"))
    print(send_request("KV/1.0 GET user42\n"))
    print(send_request("KV/1.0 DEL user42\n"))
    print(send_request("KV/1.0 GET user42\n"))
    print(send_request("KV/1.0 DEL user42\n"))
    print(send_request("KV/1.0 POTT user42 Alice).\n"))
    print(send_request("KV/1.0 STATS\n"))
    print(send_request("KV/1.0 QUIT\n"))
    print(send_request("KV/2.0 QUIT\n"))
    print(send_request("KV/1.0 PUT user42\n"))
