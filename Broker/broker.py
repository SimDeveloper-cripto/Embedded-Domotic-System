import paho.mqtt.client as mqtt
import json
from httpClient import HTTPClient


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
            self._performAction(obj.lower(), value.lower())
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
    def _performAction(obj, value):
        arduino_ip = ""  # Insert here Arduino'IP
        base_url = f"http://{arduino_ip}/{obj}"

        if obj == "led":
            match value:
                case "high":
                    http = HTTPClient(base_url + "/high")
                    http.get(params=None)
                case "low":
                    http = HTTPClient(base_url + "/low")
                    http.get(params=None)
                case _:
                    print("Wrong Request submitted!")
