import paho.mqtt.client as mqtt
import time

# Callback to manage client connections to Broker
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe("test/topic")

# Callback quando un messaggio viene pubblicato su un argomento a cui siamo iscritti
def on_message(client, userdata, msg):
    print(f"Received a message on topic {msg.topic}: {msg.payload.decode()}")

# Creare un'istanza del client MQTT
client = mqtt.Client()

# Assegnare le funzioni di callback
client.on_connect = on_connect
client.on_message = on_message

# Connettersi al broker
client.connect("localhost", 1883, 60)

# Avviare il loop per la gestione della rete
# client.loop_forever()
client.loop_start()

try:
    while True:
        print("Broker in attesa di connessioni...")
        time.sleep(1)
except KeyboardInterrupt:
    print("Interruzione da tastiera ricevuta")
    client.loop_stop()
    client.disconnect()