// Arduino Controller (parking_controller.ino)
#include <LoRa.h>
#include <Servo.h>

#define LORA_SS 10
#define LORA_RST 9
#define LORA_DIO0 2

Servo entryGate;
Servo exitGate;
Servo slotA1, slotA2, slotB1, slotB2;

bool slots[4] = {false}; // A1, A2, B1, B2

void setup() {
  Serial.begin(115200);
  entryGate.attach(3);
  exitGate.attach(5);
  slotA1.attach(6);
  slotA2.attach(7);
  slotB1.attach(8);
  slotB2.attach(9);
  
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  
  // Initialize gates
  entryGate.write(0);
  exitGate.write(0);
  closeAllSlots();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String message = "";
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }
    
    if (message.startsWith("ENTRY:")) {
      handleEntry(message.substring(6));
    } else if (message.startsWith("EXIT:")) {
      handleExit(message.substring(5));
    }
  }
}

void handleEntry(String slot) {
  int index = getSlotIndex(slot);
  if (index != -1 && !slots[index]) {
    entryGate.write(90);
    openSlot(slot);
    slots[index] = true;
    delay(3000);
    entryGate.write(0);
  }
}

void handleExit(String slot) {
  int index = getSlotIndex(slot);
  if (index != -1 && slots[index]) {
    exitGate.write(90);
    closeSlot(slot);
    slots[index] = false;
    delay(3000);
    exitGate.write(0);
  }
}

int getSlotIndex(String slot) {
  if (slot == "A1") return 0;
  if (slot == "A2") return 1;
  if (slot == "B1") return 2;
  if (slot == "B2") return 3;
  return -1;
}

void openSlot(String slot) {
  if (slot == "A1") slotA1.write(90);
  if (slot == "A2") slotA2.write(90);
  if (slot == "B1") slotB1.write(90);
  if (slot == "B2") slotB2.write(90);
  delay(1000);
}

void closeSlot(String slot) {
  if (slot == "A1") slotA1.write(0);
  if (slot == "A2") slotA2.write(0);
  if (slot == "B1") slotB1.write(0);
  if (slot == "B2") slotB2.write(0);
  delay(1000);
}

void closeAllSlots() {
  slotA1.write(0);
  slotA2.write(0);
  slotB1.write(0);
  slotB2.write(0);
}
