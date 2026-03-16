#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define EEPROM_SIZE 512
#define ONE_WIRE_BUS 4  // DS18B20 data pin

#define Pel_Pow_Relay 25  // Relay control pin
#define RELAY_PIN2 27
#define RELAY_PIN3 33
#define OFF 1
#define ON 0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  sensors.begin();

  pinMode(Pel_Pow_Relay, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  pinMode(RELAY_PIN3, OUTPUT);

  digitalWrite(Pel_Pow_Relay, OFF);

  randomSeed(analogRead(0));
}

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  Serial.print("Current Temp: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature <= 18.0) {
    digitalWrite(RELAY_PIN2, ON);
    digitalWrite(RELAY_PIN3, ON);
    digitalWrite(Pel_Pow_Relay, ON);
  } 
  else if (temperature >= 22.0) {
    digitalWrite(Pel_Pow_Relay, ON);
    digitalWrite(RELAY_PIN2, OFF);
    digitalWrite(RELAY_PIN3, OFF);
    Serial.println("Coolling");
  } 
  else if (temperature <= 20.0) {
    digitalWrite(Pel_Pow_Relay, OFF);
    delay(3000);
    digitalWrite(RELAY_PIN2, OFF);
    digitalWrite(RELAY_PIN3, OFF);
  }

  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("Start Processing");

  unsigned long startTime = millis();

  // ==== EEPROM Write Random Values ====
  for (int i = 0; i < EEPROM_SIZE; i++) {
    byte value = random(0, 256);
    EEPROM.write(i, value);
  }
  EEPROM.commit();

  // ==== Heavy Processing ====
  float dummy = 0;
  for (unsigned long i = 0; i < 1000000; i++) {
    dummy += sin(i * 0.001) * cos(i * 0.002);
  }

  // ==== EEPROM Clear ====
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();

  unsigned long endTime = millis();

  Serial.println("End Processing");
  Serial.print("Total Processing Time: ");
  Serial.print(endTime - startTime);
  Serial.println(" ms");
  Serial.println("");
  Serial.println("");

  delay(2000);  // Delay before next loop
}
