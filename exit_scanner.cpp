// ESP32-CAM Exit Scanner (exit_scanner.ino)
#include <LoRa.h>
#include <ESP32QRCodeReader.h>

#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 2

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

void setup() {
  Serial.begin(115200);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  
  reader.setup();
  reader.beginOnCore(1);
}

void loop() {
  struct QRCodeData qrCodeData;
  if (reader.receiveQrCode(&qrCodeData, 100)) {
    if (qrCodeData.valid) {
      String slot = String(qrCodeData.payload);
      LoRa.beginPacket();
      LoRa.print("EXIT:" + slot);
      LoRa.endPacket();
    }
  }
  delay(50);
}
