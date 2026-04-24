#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "ble_app.h"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

/**
 * @brief Server Callback Class
 * Task 2: Connection Guard Lab
 * - Implement onConnect and onDisconnect logic.
 * - Ensure self-healing by restarting advertising on disconnect.
 */
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println(">>> Device Connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println(">>> Device Disconnected");
      // Task 2: Self-healing - Restart advertising
      // TODO: Add code here to restart advertising when a device disconnects
      // Hint: Use the server pointer to call the advertising start method
      Serial.println(">>> Ready for new connections...");
    }
};

void setup() {
  Serial.begin(115200);
  pinMode(STATUS_LED_PIN, OUTPUT);

  // Initialize BLE Device
  BLEDevice::init(DEVICE_NAME);

  // Create BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setValue("Hello Vibe!");
  
  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  
  Serial.print("BLE Device Ready: ");
  Serial.println(DEVICE_NAME);
}

void loop() {
    // Task 2: Status Feedback via LED
    if (deviceConnected) {
        digitalWrite(STATUS_LED_PIN, HIGH); // Steady on when connected
    } else {
        // Flash LED when disconnected/advertising
        digitalWrite(STATUS_LED_PIN, (millis() / 500) % 2); 
    }

    // Task 3: RSSI Proximity Detection (Simulated/Placeholder)
    // Note: In a real Server scenario, the Server doesn't usually see the Client's RSSI 
    // unless the Client sends it back or we are in Scanning mode.
    // For this lab, we assume the student uses a scanner app to check RSSI.
    
    delay(10);
}
