from server_socket import ServerSocket


def run():
    server_socket = ServerSocket("localhost", 6969)
    try:
        server_socket.start()
    except KeyboardInterrupt:
        print("[!!!] Keyboard Interrupt Received! Server is stopping!")
    finally:
        server_socket.stop()


if __name__ == "__main__":
    run()
