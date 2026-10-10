
# 🏠 Advanced Smart Home & Office Automation System with Voice Integration

An **IoT-based Home Automation System** built on the **ESP8266 NodeMCU**, controlled through the **Blynk IoT** platform and **voice assistants**. It lets you switch lights, fans, and other appliances on or off from anywhere in the world: from a phone app, a manual switch, or just your voice.

![Platform](https://img.shields.io/badge/Platform-ESP8266%20NodeMCU-blue)
![IDE](https://img.shields.io/badge/IDE-Arduino%20IDE-00979D?logo=arduino&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Blynk-green)
![Voice](https://img.shields.io/badge/Voice-Google%20Assistant%20%7C%20Alexa-orange)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

---

## 📖 Overview

This project turns ordinary appliances into smart, Wi-Fi-connected devices. An ESP8266 NodeMCU drives a relay module that switches AC appliances, while the Blynk IoT cloud provides a real-time dashboard on your smartphone. Voice assistants are linked to the same cloud, so hands-free control works with simple spoken commands like *"Turn on the bedroom light."*

It works for both **home** and **office** setups, reducing manual effort and helping save energy.

---

## ✨ Features

- 📱 **Remote control** of appliances from anywhere via the Blynk mobile app
- 🎙️ **Voice control** through Google Assistant / Alexa integration
- 🔌 **Multi-channel relay control** (4-channel relay module, expandable)
- 🔘 **Manual switch override**, so appliances still work if Wi-Fi is down
- 🔄 **Real-time status sync** between the app, switches, and voice commands
- 📶 **Auto Wi-Fi reconnection** for reliable uptime
- 💡 **Low cost and easy to extend**: add sensors, more relays, or schedules

---

## 🧰 Tech Stack

| Category | Technology |
|---|---|
| Microcontroller | ESP8266 NodeMCU (ESP-12E) |
| IDE | **Arduino IDE** |
| Language | C / C++ (Arduino framework) |
| IoT Platform | Blynk IoT (Blynk.Cloud) |
| Voice Assistants | Google Assistant / Amazon Alexa |
| Actuators | 4-channel 5V relay module |
| Connectivity | Wi-Fi (2.4 GHz) |

---

## 🔧 Hardware Requirements

| Component | Quantity |
|---|---|
| ESP8266 NodeMCU development board | 1 |
| 4-channel 5V relay module | 1 |
| Push buttons / toggle switches (manual control) | 4 |
| 5V 2A power supply (or USB adapter) | 1 |
| Jumper wires and breadboard / PCB | as needed |
| AC appliances (lamp, fan, etc.) | as needed |

> ⚠️ **Safety warning:** This project switches mains voltage (110V/230V AC). Work only with power disconnected, use properly insulated enclosures, and ask a qualified electrician if you are not experienced with mains wiring.

---

## 🔌 Circuit & Pin Connections

Suggested pin mapping (change it in the code to suit your wiring):

| Device | NodeMCU Pin | GPIO |
|---|---|---|
| Relay 1 (Light) | D1 | GPIO5 |
| Relay 2 (Fan) | D2 | GPIO4 |
| Relay 3 (Appliance 3) | D5 | GPIO14 |
| Relay 4 (Appliance 4) | D6 | GPIO12 |
| Switch 1 | D3 | GPIO0 |
| Switch 2 | D7 | GPIO13 |
| Switch 3 | D0 | GPIO16 |
| Switch 4 | D8 | GPIO15 |
| Relay VCC / GND | VIN / GND | - |

Note: some relay modules are **active-LOW** (they switch on when the pin is LOW). Adjust the logic in the code if yours behaves the opposite way.

---

## 🏗️ System Architecture

```
 ┌──────────────┐      ┌──────────────┐
 │ Blynk Mobile │      │ Voice Assist │
 │     App      │      │ Google/Alexa │
 └──────┬───────┘      └──────┬───────┘
        │                     │
        └────────┬────────────┘
                 ▼
          ┌─────────────┐
          │ Blynk Cloud │
          └──────┬──────┘
                 │ Wi-Fi
                 ▼
          ┌─────────────┐      ┌──────────────┐
          │   ESP8266   │─────▶│ Relay Module │───▶ Appliances
          │   NodeMCU   │      └──────────────┘
          └──────▲──────┘
                 │
          Manual Switches
```

---

## 🚀 Getting Started

### 1. Set up Arduino IDE

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open **File → Preferences** and add this URL under *Additional Boards Manager URLs*:
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Go to **Tools → Board → Boards Manager**, search for **esp8266**, and install it.
4. Select **Tools → Board → NodeMCU 1.0 (ESP-12E Module)**.

### 2. Install libraries

Open **Sketch → Include Library → Manage Libraries** and install:

- **Blynk** (by Volodymyr Shymanskyy)
- **ESP8266WiFi** (included with the ESP8266 board package)

### 3. Configure Blynk IoT

1. Create an account at [blynk.cloud](https://blynk.cloud) and install the Blynk app.
   dashboard used here: https://blynk.cloud/dashboard/707549/global/devices/216859/organization/707549/devices/2158467/dashboard
3. Create a **Template** and add **Datastreams** (Virtual Pins V1 to V4, type `Integer`, 0 to 1).
4. Create a **Device** from the template. Note your **Template ID**, **Template Name**, and **Auth Token**.
5. Build a dashboard with 4 switch widgets mapped to V1 to V4.

### 4. Upload the code

Add your credentials at the top of the sketch:

```cpp
#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
```

Then select the correct COM port and click **Upload**.

### 5. Enable voice control

Voice assistants are connected to the same Blynk datastreams, so a spoken command ends up as the same on/off signal your app sends.

- **Google Assistant / Alexa:** link your account through an automation bridge such as **IFTTT** (or a similar webhook service) that calls the Blynk HTTPS API, for example:
  ```
  https://blynk.cloud/external/api/update?token=YOUR_AUTH_TOKEN&v1=1
  ```
- Create one "on" and one "off" applet or routine per appliance, with phrases like *"Turn on the light"* and *"Turn off the fan"*.

---

## 🗣️ Example Voice Commands

| Command | Action |
|---|---|
| "Hey Google, turn on the light" | Relay 1 ON |
| "Hey Google, turn off the fan" | Relay 2 OFF |
| "Alexa, turn on the office lamp" | Relay 3 ON |
| "Alexa, turn off everything" | All relays OFF |

*(Exact phrases depend on the names and routines you configure.)*

---

## 📂 Project Structure

```
├── SmartHome_Automation/
│   └── SmartHome_Automation.ino   # Main Arduino sketch
├── circuit/                       # Circuit diagram / schematics
├── images/                        # Screenshots and demo photos
└── README.md
```

---

## 🛠️ Troubleshooting

| Problem | Possible fix |
|---|---|
| Board not detected | Install the CH340 / CP2102 USB driver |
| Won't connect to Wi-Fi | Use a 2.4 GHz network; the ESP8266 doesn't support 5 GHz |
| Relay behaves inverted | Your module is active-LOW; flip the HIGH/LOW logic |
| Blynk shows "Offline" | Recheck the Auth Token, Template ID, and Wi-Fi credentials |
| Random resets | Use a stable 5V 2A supply; relays can cause voltage dips |

---

## 🔮 Future Improvements

- 🌡️ Temperature and humidity monitoring (DHT11/DHT22)
- ⏰ Scheduling and timers
- ⚡ Energy consumption monitoring
- 🔔 Push notifications and alerts
- 🌐 MQTT / Home Assistant integration
- 🔒 OTA (over-the-air) firmware updates

---

## 🤝 Contributing

Contributions are welcome! Fork the repo, create a feature branch, and open a pull request.

## 📜 License

This project is licensed under the **MIT License**. See the `LICENSE` file for details.

## 👤 Author

**Your Name**
GitHub: [@your-username](https://github.com/your-username)

⭐ If you found this project useful, please consider giving it a star!
