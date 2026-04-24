#ifndef BLE_APP_H
#define BLE_APP_H

/**
 * @brief BLE Device Identity Configuration
 * 
 * Task 1: Name Master Lab
 * - Update DEVICE_NAME to "Vibe-Student-XX" where XX is your seat number.
 * - Ensure the SERVICE_UUID is unique or use the standard one provided.
 */

#define DEVICE_NAME "Vibe-Student-99"
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Hardware Pin Definitions
#define STATUS_LED_PIN 2  // Standard onboard LED for ESP32 DevKit

#endif // BLE_APP_H
