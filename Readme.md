# Overview: A Domotic System For Your House

## Requirements

* __OS__: Windows 11
* __Python__: 3.12
* __Zig__: 0.13.0
* __Arduino Uno R4 Wifi__

Shout out to: <https://github.com/Not-Nik/raylib-zig.git>. <br />
Quick setup if you also want to try it: <br />

```bash
mkdir <folder-name> && cd <folder-name>
git clone https://github.com/Not-Nik/raylib-zig.git
./project_setup.ps1
cd Project && zig build run
```

## Project's Structure

The frontend consists in a Zig app made with Raylib and Raygui which communicates with a Python script via __Socket__. <br />
Architecture developed: __client-server__, with the Zig app being the client. <br />
The Python script communicates via __HTTP__ with the Arduino (it provides some endpoints), which handles all the user requests to turn __on/off__ the lights. <br />
No worries, you can extend the work by making simple changes (the code is really easy to follow). You could also, for example, automate servo motors! <br /> 

I'll show you the json exchanged between communications:

```json
{
  "object": "led", // The type of the object you want to control
  "value": "HIGH", // HIGH or LOW
  "number": "1",   // A number from 1 to 4
}
```

## Run

* __Step 1__: Modify these two lines and then upload to your Arduino. <br />

```bash
const char* WIFI_SSID = ""; /* Here insert your SSID */
const char* WIFI_PASS = ""; /* Here insert your PASSWORD */
```

Then, __run__ the code and have a look at the Serial Monitor. __Save__ the IP Address that will be shown. <br />
Do not stop the execution. <br />

* __Step 2__: Setup Python script. <br />

* You could use PyCharm to do that, but install dependency:

```bash
cd python_backend_server_socket
pip install python-dotenv requests
```

In the same folder create a __.env__ file in which you are going to specify the following:

```bash
ARDUINO_IP="" // Paste the Arduino IP Address!
```

* __Step 3__: Run scripts separately on two different terminals: <br />

```bash
cd python_backend_server_socket
./execute.bat
```

```sh
cd python_backend_server_socket
chmod +x execute.sh
.\execute.sh
```

```bash
cd zig_app/Project
zig build run
```

### TODO: CREATE DOCKER CONTAINER FOR THE APP
