# LoRa Device

[ESP32 Heltec WiFi LoRa 32 (V1)](https://heltec.org/project/wifi-lora-32/) code to work with the [LoRa Server](https://github.com/douglasJovenil/lora-server)

## ☁️ Links
- [LoRa Server](https://github.com/douglasJovenil/lora-server)

## 💻 Project

#### Burning Firmware

![Burning Firmware](docs/images/00_burning_firmware.png)

#### Serial Output

![Serial Output](docs/images/01_serial_output.png)

## 🚀 Technologies

<img align="left" alt="C++" width="26px" src="https://raw.githubusercontent.com/github/explore/80688e429a7d4ef2fca1e82350fe8e3517d3494d/topics/cpp/cpp.png" /> C++

<img align="left" alt="PlatformIO" width="26px" src="docs/images/02_platformio.png" /> PlatformIO

<img align="left" alt="Python" width="26px" src="https://raw.githubusercontent.com/github/explore/80688e429a7d4ef2fca1e82350fe8e3517d3494d/topics/python/python.png" /> Python3.7+

## 🏃 Usage

Before you start the server theres some commands that you have to run, just copy and paste one by one the commands bellow:

``` 
git clone https://github.com/douglasJovenil/lora-device
cd lora-device
pio init -b heltec_wifi_lora_32 --ide vscode
pio lib install

cd src
python3.8 setup.py

cd ..
pio run -t upload && pio device monitor -b 115200
```
