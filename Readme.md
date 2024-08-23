# Overview: A Domotic System For Your House

The project is not finished. It does not work for now, so please don't use it :)

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
The Python script communicates via __HTTP__ with the Arduino (it provides some endpoints), which handles all the user requests. <br />

* Show JSON package structure. <br />

## Run

* __Step 1__: Modify these two lines and then upload to your Arduino. <br />

```bash
const char* WIFI_SSID = ""; /* Here insert your SSID */
const char* WIFI_PASS = ""; /* Here insert your PASSWORD */
```

*__Step 2__: Run Python Script. <br />

```bash
cd python_backend_server_socket
./execute.bat
```

* __Step 3__: Run Zig Application. <br />

```bash
cd zig_app/Project
zig build run
```

## Docker

Insert here instructions to run docker container. <br />