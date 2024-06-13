import paho.mqtt.client as mqtt
import json
import requests


class Broker:
    def __init__(self, host, port, topics=None):
        self._host   = host
        self._port   = port
        self._topics = topics if topics is not None else []
        self.client  = mqtt.Client()

        # Callbacks
        self.client.on_connect = self.onConnect
        self.client.on_message = self.onMessage

    @property
    def host(self):
        return self._host

    @host.setter
    def host(self, hostValue):
        self._host = hostValue

    @property
    def port(self):
        return self._port

    @port.setter
    def port(self, portValue):
        self._port = portValue

    @property
    def topics(self):
        return self._topics

    @topics.setter
    def topics(self, topics):
        self._topics = topics

    def onConnect(self, client, userdata, flags, rc):
        for topic in self._topics:
            client.subscribe(topic)

    def onMessage(self, client, userdata, msg):
        try:
            content = json.loads(msg.payload.decode())
            obj     = content["object"]
            value   = content["value"]
            print(f"Object: {obj}, Value: {value}")
            self._performAction(obj.lower(), value.lower(), content)
        except json.JSONDecodeError as e:
            print(f"Failed to decode JSON: {e}")
        except KeyError as e:
            print(f"Missing key in JSON: {e}")

    def start(self):
        self.client.connect(self._host, self._port, 60)
        self.client.loop_start()

    def stop(self):
        self.client.loop_stop()
        self.client.disconnect()

    @staticmethod
    def _performAction(obj, value, content):
        arduino_ip = "192.168.1.25"  # Insert here Arduino'IP (should use .env file)
        base_url = f"http://{arduino_ip}/{obj}/{value}"

        print(f"BASE URL: {base_url}")

        if obj == "led":
            if "number" in content:
                led_number = content["number"]
                url = f"{base_url}/{led_number}"
                response = requests.get(url)
                if response.status_code == 200:
                    print("Request successful [200 OK]")
                else:
                    print(f"Response received from Arduino: {response}")
