import time
from broker import Broker


def run():
    topics = ["lights/topic"]  # Should think about other topics (doors, for example)
    broker = Broker("localhost", 1883, topics=topics)
    broker.start()

    try:
        print("Broker is waiting for connections...")
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("Keyboard Interrupt received!")
        broker.stop()


if __name__ == "__main__":
    run()
