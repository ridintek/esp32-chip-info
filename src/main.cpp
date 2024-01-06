#include <Arduino.h>

esp_chip_info_t chip;
esp_flash_t flash;

String model = "Unknown";

void setup()
{
  pinMode(2, OUTPUT); // Built-in LED.
  Serial.begin(115200);

  esp_chip_info(&chip);

  String chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
  chipId.toUpperCase();

  Serial.print("ESP32 model: ");

  switch (chip.model)
  {
  case 1:
    model = "ESP32";
    break;
  case 2:
    model = "ESP32S2";
    break;
  case 9:
    model = "ESP32S3";
    break;
  case 5:
    model = "ESP32C3";
    break;
  case 6:
    model = "ESP32H2";
    break;
  }

  Serial.println(model);
  Serial.printf("Chip Model: %s\n", ESP.getChipModel());
  Serial.printf("Chip ID: %s\n", chipId.c_str());
  Serial.printf("Chip Revision: %d\n", chip.revision);
  Serial.printf("Core: %d\n", chip.cores);
  Serial.printf("Clock Speed: %dMHz\n", ESP.getCpuFreqMHz());
  Serial.println("Features: ");

  if (chip.features & CHIP_FEATURE_WIFI_BGN)
  {
    Serial.println("- WIFI BGN");
  }

  if (chip.features & CHIP_FEATURE_BT)
  {
    Serial.println("- BLUETOOTH");
  }

  if (chip.features & CHIP_FEATURE_BLE)
  {
    Serial.println("- BLUETOOTH LE");
  }

  if (chip.features & CHIP_FEATURE_EMB_FLASH)
  {
    Serial.println("- EMBEDDED FLASH MEMORY");
  }
  else
  {
    Serial.println("- EXTERNAL FLASH MEMORY");
  }

  Serial.printf("Flash Memory Size: %f MB, %d MiB, %d bytes\n",
                (float)spi_flash_get_chip_size() / (1000.0F * 1000.0F),
                spi_flash_get_chip_size() / (1024 * 1024),
                spi_flash_get_chip_size());

  if (chip.features & CHIP_FEATURE_EMB_PSRAM)
  {
    Serial.println("- EMBEDDED PSRAM");
  }

  if (chip.features & CHIP_FEATURE_IEEE802154)
  {
    Serial.println("- IEEE 802.15.4");
  }
}

void loop()
{
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(1000);
}
