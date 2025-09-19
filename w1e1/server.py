import socket
import threading

store = {}

def handle_client(conn, addr):
    print(f"Client connected: {addr}")
    with conn:
        while True:
            try:
                data = conn.recv(1024)
                if not data:
                    break
                request = data.decode("utf-8").strip()
                print("Request:", request)

                # Check version
                if not request.startswith("KV/1.0"):
                    response = "426 UPGRADE_REQUIRED\n"
                    conn.sendall(response.encode("utf-8"))
                    continue

                parts = request.split()
                if len(parts) < 2:
                    response = "400 BAD_REQUEST\n"
                else:
                    cmd = parts[1].upper()
                    if cmd == "PUT":
                        if len(parts) < 4:
                            response = "400 BAD_REQUEST\n"
                        else:
                            key, value = parts[2], parts[3]
                            if key in store:
                                store[key] = value
                                response = "200 OK\n"
                            else:
                                store[key] = value
                                response = "201 CREATED\n"
                    elif cmd == "GET":
                        if len(parts) < 3:
                            response = "400 BAD_REQUEST\n"
                        else:
                            key = parts[2]
                            if key in store:
                                response = f"200 OK {store[key]}\n"
                            else:
                                response = "404 NOT_FOUND\n"
                    elif cmd == "DEL":
                        if len(parts) < 3:
                            response = "400 BAD_REQUEST\n"
                        else:
                            key = parts[2]
                            if key in store:
                                del store[key]
                                response = "204 NO_CONTENT\n"
                            else:
                                response = "404 NOT_FOUND\n"
                    elif cmd == "STATS":
                        response = f"200 OK {len(store)} keys\n"
                    elif cmd == "QUIT":
                        response = "200 OK Bye\n"
                        conn.sendall(response.encode("utf-8"))
                        break
                    else:
                        response = "400 BAD_REQUEST\n"

                conn.sendall(response.encode("utf-8"))

            except Exception as e:
                conn.sendall(b"500 SERVER_ERROR\n")
                break

def start_server(host="127.0.0.1", port=5050):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((host, port))
        s.listen()
        print(f"KVSS Server listening on {host}:{port}")
        while True:
            conn, addr = s.accept()
            threading.Thread(target=handle_client, args=(conn, addr)).start()

if __name__ == "__main__":
    start_server()
