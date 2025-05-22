/* 
 * Program Title:
 * IS3750_Arduino_Traffic_Light_Example
 * 
 * Internal Reference: ISFW1039
 *
 * Description:
 * This example demonstrates how to use the IS3750 Addressable LED Controller
 * chip with the Arduino platform.
 *
 * The sketch simulates a simple traffic light sequence: 
 * green → yellow → red → green.
 *
 * If you're using the Kappa3750Ard or Kappa3750Rasp Evaluation Board,
 * set the "I2C Speed Selector" jumper to 100 kHz.
 *
 * For more information, visit the product page:
 * https://www.inacks.com/is3750
 *
 * https://www.inacks.com
 */


#include <Wire.h>

// I2C device address of the IS3750 chip:
#define IS3750_I2C_ADDRESS    0x12

// Memory Map:
#define IS3750_REGISTER_SHOW        0x00
#define IS3750_REGISTER_LED1_RED    0x01
#define IS3750_REGISTER_LED1_GREEN  0x02
#define IS3750_REGISTER_LED1_BLUE   0x03
#define IS3750_REGISTER_LED2_RED    0x04
#define IS3750_REGISTER_LED2_GREEN  0x05
#define IS3750_REGISTER_LED2_BLUE   0x06
#define IS3750_REGISTER_LED3_RED    0x07
#define IS3750_REGISTER_LED3_GREEN  0x08
#define IS3750_REGISTER_LED3_BLUE   0x09


void writeLedRegister(uint16_t registerAddress, uint8_t bright) {
  // Start the I2C communications to the IS3750 chip. 
  Wire.beginTransmission(IS3750_I2C_ADDRESS); 

  // Send the 16-bit Holding Register address (2 bytes).
  Wire.write((registerAddress >> 8) & 0xFF); // High byte.
  Wire.write(registerAddress & 0xFF);        // Low byte.

  // Send the 8-bit data (the brightness).
  Wire.write(bright);        

  // End the I2C communications. 
  Wire.endTransmission();
}

// This routine updates the LEDs. 
void showLeds(void) {
  // Write a '1' to the SHOW register (address 0x00)
  // to trigger rendering based on the current memory map contents.
  writeLedRegister(IS3750_REGISTER_SHOW, 1); 
}

// This routine sets all the LED registers to 0. 
void clearAllLedRegisters(void) {
  uint16_t i;

  // Write 0 to all LED control registers.
  for (i = 1; i <= 1200; i++) {
    writeLedRegister(i, 0);
  }
}

void setup() {
  Wire.begin(); // Initialize the I2C interface.
}

void loop() {
  
  // Let's do color green:
  clearAllLedRegisters(); // Clear all memory map. 
  writeLedRegister(IS3750_REGISTER_LED1_GREEN, 5); // Set LED1 to green (brightness = 5)
  showLeds();
  delay(500);
     
  // Let's do color yellow:
  clearAllLedRegisters(); // Clear all memory map.
  // Set LED2 to yellow by combining red and green (brightness = 5 each)
  writeLedRegister(IS3750_REGISTER_LED2_RED, 5);  
  writeLedRegister(IS3750_REGISTER_LED2_GREEN, 5);
  showLeds();
  delay(500);

  // Let's do color blue:
  clearAllLedRegisters();// Clear all memory map.
  writeLedRegister(IS3750_REGISTER_LED3_BLUE, 5); // Set LED3 to blue (brightness = 5)
  showLeds();
  delay(500);

}
