#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // ESP32 I2C pins
  Wire.begin(21, 22);

  // Start ADS1115 på default adresse 0x48
  if (!ads.begin(0x48)) {
    Serial.println("Kunne ikke finde ADS1115. Tjek ledninger og adresse.");
    while (1) {
      delay(1000);
    }
  }

  // Sæt gain:
  // GAIN_ONE = +/-4.096V
  // MEN husk stadig: input maa ikke overstige VDD hvis modulet kører på 3.3V
  ads.setGain(GAIN_ONE);

  Serial.println("ADS1115 fundet!");
  Serial.println("Laeser kanaler A0-A3...");
}

void loop() {
  int16_t adc0 = ads.readADC_SingleEnded(0);
  int16_t adc1 = ads.readADC_SingleEnded(1);
  int16_t adc2 = ads.readADC_SingleEnded(2);
  int16_t adc3 = ads.readADC_SingleEnded(3);

  // For GAIN_ONE er LSB = 0.125 mV pr bit
  float v0 = adc0 * 0.125f / 1000.0f;
  float v1 = adc1 * 0.125f / 1000.0f;
  float v2 = adc2 * 0.125f / 1000.0f;
  float v3 = adc3 * 0.125f / 1000.0f;

  Serial.println("----- ADS1115 -----");

  Serial.print("A0: ");
  Serial.print(adc0);
  Serial.print("  |  ");
  Serial.print(v0, 4);
  Serial.println(" V");

  Serial.print("A1: ");
  Serial.print(adc1);
  Serial.print("  |  ");
  Serial.print(v1, 4);
  Serial.println(" V");

  Serial.print("A2: ");
  Serial.print(adc2);
  Serial.print("  |  ");
  Serial.print(v2, 4);
  Serial.println(" V");

  Serial.print("A3: ");
  Serial.print(adc3);
  Serial.print("  |  ");
  Serial.print(v3, 4);
  Serial.println(" V");

  delay(500);
}