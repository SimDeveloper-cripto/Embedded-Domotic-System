# A Domotic System For Your House

## Requirements

* OS: Windows 11
* Python: 3.12
* Zig: 0.13.0
* Arduino Uno R4 Wifi

The frontend consists in a Zig app made with Raylib and Raygui. <br />
Shout out to: https://github.com/Not-Nik/raylib-zig.git. <br />

Quick setup if you also want to try it: <br />

```bash
mkdir <folder-name> && cd <folder-name>
git clone https://github.com/Not-Nik/raylib-zig.git
./project_setup.ps1
cd Project && zig build run
```

## Project's Structure

## Run

* Step 1: Modify these two lines and then upload to your Arduino. <br />

```bash
const char* WIFI_SSID = ""; /* Here insert your SSID */
const char* WIFI_PASS = ""; /* Here insert your PASSWORD */
```

* Step 2: Run Python Script. <br />

```bash
cd python_backend_server_socket
./execute.bat
```

* Step 3: Run Zig Application. <br />

```bash
cd zig_app/Project
zig build run
```

## Docker

Insert here instructions to run docker container. <br />