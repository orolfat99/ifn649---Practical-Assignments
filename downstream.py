import paho.mqtt.client as mqtt
import serial

def on_connect(client, userdata, flags, rc): # func for making connection
	print(f"Connected to MQTT Server {ADD} at port {PORT}")
	print("Connection returned result: " + str(rc) )
	topic = "ifn649"
	client.subscribe(topic)
	print(f"Subcribeed to topic: {topic}")
	
def on_message(client, userdata, msg): # Func for Sending msg
	print("receive message!")
	print(msg.topic+" "+str(msg.payload))
	print("relaying to teensy over BT....")
	
	#Code from last week bt.py
	ser = serial.Serial("/dev/rfcomm0",9600)
	ser.write(msg.payload)

ADD = "3.25.53.188"
PORT = 1883

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(ADD, PORT, 60)
client.loop_forever()
