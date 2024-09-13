import os
import json
import socket
import requests
from dotenv import load_dotenv


load_dotenv()


class ServerSocket:
    def __init__(self, host, port):
        self.__host   = host
        self.__port   = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.__host, self.__port))
        self.server_socket.listen(10)  # 10 MAX CONCURRENT CONNECTIONS

    @property
    def host(self):
        return self.__host

    @host.setter
    def host(self, hostValue):
        self.__host = hostValue

    @property
    def port(self):
        return self.__port

    @port.setter
    def port(self, portValue):
        self.__port = portValue

    def start(self):
        print(f"[+] Server Socket started on {self.__host}:{self.__port}, waiting for connections!")
        try:
            while True:
                client_socket, client_address = self.server_socket.accept()
                print(f"[+] Accepted Connection from {client_address}")

                try:
                    self.__handle_client(client_socket)
                except Exception as e:
                    print(f"[-] Error Handling the Client: {e}")
        except KeyboardInterrupt:
            print(f"[-] Server Socket is Shutting Down...")
        finally:
            print(f"[-] Server Socket is now closed.")
            self.stop()

    def stop(self):
        self.server_socket.close()

    def __handle_client(self, client_socket):
        try:
            data = client_socket.recv(1024).decode('utf-8')
            if not data:
                return

            print(f"    [++] Received Data: {data}")
            content = json.loads(data)
            obj = content["object"]
            value = content["value"]
            print(f"    [++] Object: {obj}, Value: {value}")
            self.__performAction(obj.lower(), value.upper(), content)

            # RESPOND TO CLIENT
            response = json.dumps({"Status": "Success", "Message": f"Received {obj.upper()} with value {value}"})
            client_socket.sendall(response.encode('utf-8'))
        except json.JSONDecodeError as e:
            print(f"    [--] Failed to Decode JSON: {e}")
        except KeyError as e:
            print(f"    [--] Missing Key in JSON: {e}")
        finally:
            client_socket.close()

    @staticmethod
    def __performAction(obj, value, content):
        arduino_ip = os.getenv('ARDUINO_IP')
        base_url = f"http://{arduino_ip}/{obj}/{value}"

        print(f"    [++] BASE URL: {base_url}")

        if obj == "led":
            if "number" in content:
                led_number = content["number"]
                url = f"{base_url}/{led_number}"
                print(f"    [++] Sending request to {url}")
                try:
                    response = requests.get(url)
                    print(f"    [++] REQUEST: {url}")
                    if response.status_code == 200:
                        print("    [++] Request successful [200 OK]")
                    else:
                        print(f"    [++] Response received from Arduino: {response}")
                except Exception as e:
                    print(f"    [--] Error during request: {e}")
