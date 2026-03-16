# OPTERS-Thermal-Management
Low-cost thermoelectric temperature regulation system (OPTERS) for autonomous sensor nodes in extreme desert environments. Uses an ESP32-controlled Peltier module with PWM-based bidirectional heating/cooling to maintain stable internal temperatures for off-grid, solar-powered IoT deployments.
This prototype implements a thermoelectric temperature management controller using an ESP32 (or compatible Arduino-IDE board) and a DS18B20 temperature sensor. The system monitors internal temperature and controls relay outputs connected to a thermoelectric cooling module (Peltier system) and related circuitry.
The controller also performs EEPROM stress testing and computational load simulation to measure processing time and demonstrate system performance during operation.
The main goal of the program is to:
Monitor internal temperature
Control thermoelectric cooling hardware via relays
Maintain temperature within a defined range
Simulate processing workload
Measure processing performance

Hardware Components
The system uses the following hardware components:
ESP32 microcontroller
DS18B20 digital temperature sensor
Relay module
Thermoelectric cooling module (Peltier device)
EEPROM (internal flash emulation)

Pin Configuration
Component
Pin
DS18B20 Data Pin
GPIO 4
Peltier Power Relay
GPIO 25
Relay Output 2
GPIO 27
Relay Output 3
GPIO 33

Constants used in the code:
OFF = 1
ON = 0

These values correspond to active-low relay modules, where LOW activates the relay.

Libraries Used
EEPROM Library
Handles reading and writing to the ESP32's flash-based EEPROM.
OneWire Library
Used for communication with the DS18B20 sensor over the OneWire protocol.
DallasTemperature Library
Simplifies temperature measurement from the DS18B20 sensor.

Program Workflow
The program runs in a continuous loop performing the following tasks:
Read Temperature
Control Thermoelectric System
Simulate Processing Load
Write and Clear EEPROM
Measure Processing Time

Temperature Monitoring
The DS18B20 sensor measures the current temperature.
Example output in the serial monitor:
Current Temp: 21.50 °C

Temperature is retrieved using:
sensors.requestTemperatures();
float temperature = sensors.getTempCByIndex(0);


Temperature Control Logic
The system controls relays depending on temperature thresholds.
Cooling Mode
Activated when temperature rises above 22°C
Actions performed:
Turn ON Peltier power relay
Disable RELAY_PIN2 and RELAY_PIN3
Print status message
Coolling


Low Temperature Mode
Activated when temperature drops below 18°C
Actions performed:
Enable RELAY_PIN2
Enable RELAY_PIN3
Turn ON Peltier power relay

Stabilization Mode
Activated when temperature drops below 20°C
Actions performed:
Turn OFF Peltier relay
Wait 3 seconds
Turn OFF auxiliary relays
This helps prevent unnecessary cooling once the target temperature is reached.

EEPROM Processing Test
The system writes random values to the entire EEPROM memory, simulating heavy data operations.
for (int i = 0; i < EEPROM_SIZE; i++)
{
    byte value = random(0,256);
    EEPROM.write(i,value);
}

After writing the data, the program commits the changes:
EEPROM.commit();

Then it clears the EEPROM by writing zeros.
This simulates memory usage during operation.

Computational Load Simulation
The program performs a heavy mathematical loop to simulate processing load.
for (unsigned long i = 0; i < 1000000; i++)
{
    dummy += sin(i * 0.001) * cos(i * 0.002);
}

This represents computational tasks such as:
sensor processing
control algorithms
communication tasks

Processing Time Measurement
The system measures total processing time using the millis() function.
unsigned long startTime = millis();

After completing all operations:
unsigned long endTime = millis();

The difference is printed:
Total Processing Time: XXXX ms

Example output:
Start Processing
End Processing
Total Processing Time: 842 ms


Serial Monitor Output Example
Typical output in the Arduino Serial Monitor:
Current Temp: 23.10 °C

Coolling

Start Processing
End Processing
Total Processing Time: 845 ms


System Behavior Summary
Temperature
System Action
≥ 22°C
Cooling mode activated
≤ 18°C
Low temperature control mode
≤ 20°C
Cooling stops


Delay and Loop Timing
After completing one full cycle, the program waits:
delay(2000);

This provides a 2-second pause before repeating the loop.

Notes
The relay logic assumes active-low relay modules.
EEPROM size is configured as 512 bytes.
The program is compatible with ESP32 Arduino framework.
Processing load simulation is included for testing purposes.


License
This project is intended for educational and research use, particularly for thermoelectric thermal management systems in embedded environments.

