# ESP32 Temperature Sensor — Network Security Lab

A home lab project built to learn networking and security fundamentals
by watching real traffic move across the network, not just reading about
it.

An ESP32 reads temperature from a DHT22 sensor and sends each reading to
a small Python server over Wi-Fi. The project was built twice: once over
plain HTTP, and once over HTTPS (TLS), to compare what the traffic looks
like in each case using Wireshark.

## Why this project

This was a hands-on way to study:
- How devices get an IP address and resolve each other on a local
  network (DHCP, ARP)
- How a TCP connection and an HTTP request actually look on the wire
- The real difference encryption makes, not just in theory but in a
  packet capture
- Basic attack and defense thinking: sending forged data to an
  unauthenticated server, then fixing it

Full write-up with the side-by-side packet capture comparison:
[report.md](./report.md)

## Simulation

Before wiring the real hardware, the sensor logic and wiring were tested
in a simulator:
[ESP32 + DHT22 simulation on Wokwi](https://wokwi.com/projects/479240661179255809)

## Hardware

- ESP32 DOIT DevKit (WROOM-32)
- DHT22 temperature and humidity sensor
- Breadboard and jumper wires
- A computer on the same Wi-Fi network to run the server

## Project structure

```
esp32-temperature-sensor/
├── esp32_http/
│   └── esp32_http.ino        # Sends readings over plain HTTP
├── esp32_https/
│   └── esp32_https.ino       # Sends readings over HTTPS (TLS)
├── server.py                 # Python server, HTTP version
├── tls_server.py             # Python server, HTTPS version
├── certs/                    # Self-signed certificate (not included, see below)
├── captures/                 # Wireshark screenshots
└── report.md                 # Full comparison write-up
```

## Wiring

| DHT22 pin | ESP32 pin |
|---|---|
| VCC | 3V3 |
| DATA | GPIO 4 |
| GND | GND |

## Setup

### 1. Server (HTTP)
```bash
python3 server.py
```
Runs on port 8080.

### 2. Server (HTTPS)
Generate a self-signed certificate first:
```bash
mkdir certs
openssl req -x509 -newkey rsa:2048 -keyout certs/server.key -out certs/server.crt -days 365 -nodes -subj "/CN=YOUR_SERVER_IP"
```
Then run:
```bash
python3 tls_server.py
```
Runs on port 8443.

### 3. ESP32
Open either `esp32_http.ino` or `esp32_https.ino` in the Arduino IDE
with ESP32 board support installed, then:

1. Replace `YOUR_WIFI_SSID` and `YOUR_WIFI_PASSWORD` with your network
   credentials.
2. Find your computer's local IP address (`hostname -I` on Linux,
   `ipconfig` on Windows) and replace `YOUR_SERVER_IP`.
3. Upload to the board and open the Serial Monitor at 115200 baud to
   confirm it connects and starts sending readings.

### 4. Firewall
If your computer has a firewall active (such as `ufw` on Linux), allow
incoming connections on the port you're using:
```bash
sudo ufw allow from YOUR_NETWORK_RANGE to any port 8080 proto tcp
sudo ufw allow from YOUR_NETWORK_RANGE to any port 8443 proto tcp
```

## Capturing traffic

1. Open Wireshark on the computer running the server, on the Wi-Fi
   interface.
2. Filter by the ESP32's IP address: `ip.addr == ESP32_IP`
3. Restart the ESP32 to capture the connection from the start.
4. Right-click a packet on the relevant TCP stream and choose
   **Follow → TCP Stream** to see the request content.

See [report.md](./report.md) for the full comparison of what shows up
in each case.

## Key finding

Over HTTP, the temperature value and the full request were visible in
plain text to anyone capturing traffic on the same network. Over HTTPS,
the same data appeared as unreadable encrypted bytes, with only the TLS
handshake itself visible.

## Known limitations

- The server accepts requests from any sender without authentication —
  anyone on the network can send a fake reading.
- The HTTPS version uses a self-signed certificate that the device
  accepts without validating who issued it, which protects the data in
  transit but does not confirm the server's identity.

## Next steps

- Add a shared token so the server only accepts requests from the known
  device
- Pin the server's certificate on the device instead of skipping
  validation
- Repeat the comparison using MQTT with and without TLS