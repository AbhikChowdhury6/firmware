#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif
/* -----------------------------------------------------------------------*/
    #define FACTORYRESET_ENABLE         1
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"
/*=========================================================================*/
// IMU Connections With Feather 32u4 BLE :
//   [       IMUs        ]          [    Feather     ]
//  bnoA_SCL & bnoB_SCL      <->           SCL
//  bnoA_SDA & bnoB_SDA      <->           SDA
//  bnoA_Vin & bnoB_Vin      <->           3v
//  bnoA_GND & bnoB_GND      <->           GND
#define BLUEFRUIT_HWSERIAL_NAME   Serial1
#define BNO055_SAMPLERATE_DELAY_MS (10) // Sample Rate Delaying Data to Serial Monitor 
Adafruit_BNO055 bnoA = Adafruit_BNO055(BNO055_ADDRESS_A, 0x28); // IMU With bnoA_ADR<->bnoA_GND to Make i2c Address 0x28 or Address A
//Adafruit_BNO055 bnoB = Adafruit_BNO055(BNO055_ADDRESS_B, 0x29); // IMU With bnoB_ADR<->bnoB_Vin to Make i2c Address 0x29 or Address B
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
void error(const __FlashStringHelper*err)
{
  Serial.println(err);
  while (1);
}
void setup()
{
  while (!Serial1);  // required for Flora & Micro
  delay(100);
  
  Serial.begin(115200);
  Serial1.begin(115200);
  ble.begin();
  Serial1.print(F("Initialising the Bluefruit LE module: "));
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial1.println( F("OK!") );
 /* if ( FACTORYRESET_ENABLE )
    {
      Serial.println(F("Performing a factory reset: "));
      if ( ! ble.factoryReset() )
      {
        error(F("Couldn't factory reset"));
      }
    }
*/
  if (!bnoA.begin())
  {
    Serial.print("Ooops, BNO055(A) not detected (ADR <-> GND IMU)");
    while (1);
  }
  
 /* if (!bnoB.begin())
  {
    Serial.print("Ooops, BNO055(B) not detected (ADR <-> Vin IMU)");
    while (1);
  } */
  delay(1000);
  
  bnoA.setExtCrystalUse(true);
 //  bnoB.setExtCrystalUse(true);
  
  ble.echo(true);
  ble.println("AT+BLEUARTTX=");
}
// Display sensor calibration status for IMU 1 
void displayCalStatusA(void)
{
  // Four Calibration values between [0,3] with 0 being Uncalibration and 3 being fully calibrated
  // Data Displayed As 0 Should not be used until the systems value is either 1,2 or 3
  uint8_t system1, gyro1, accel1, mag1;
  system1 = gyro1 = accel1 = mag1 = 0;
  bnoA.getCalibration(&system1, &gyro1, &accel1, &mag1);
  
  // Displays '!' if BNO A Is Uncalibrated and Data should not be used
  ble.print("\t\t");
  if ((!system1))
  {
    ble.print("!");
  }
  
  // IMU A: calibration status for the System, Gyroscope, Accelerometer, and Magnetometer
  ble.print("IMU1:");
  ble.print("Sys:");
  ble.print(system1, DEC);
  ble.print(" G:");
  ble.print(gyro1, DEC);
  ble.print(" A:");
  ble.print(accel1, DEC);
  ble.print(" M:");
  ble.print(mag1, DEC);
}
/* void displayCalStatusB(void)
{
  uint8_t system2, gyro2, accel2, mag2;
  system2 = gyro2 = accel2 = mag2 = 0;
  bnoB.getCalibration(&system2, &gyro2, &accel2, &mag2);
// Displays '!' if the systems sensor is uncalibrated and not to be used
  ble.print("\t\t");
  if ((!system2))
  {
    ble.print("!");
  }
  
  //IMU B: calibration status for the System, Gyroscope, Accelerometer, and Magnetometer
  ble.print("IMU2:");
  ble.print("Sys:");
  ble.print(system2, DEC);
  ble.print(" G:");
  ble.print(gyro2, DEC);
  ble.print(" A:");
  ble.print(accel2, DEC);
  ble.print(" M:");
  ble.print(mag2, DEC);
} */
void loop()
{
  ble.setMode(BLUEFRUIT_MODE_DATA);
  sensors_event_t event;
  bnoA.getEvent(&event);
  imu::Quaternion q = bnoA.getQuat();
  float zax = 180/M_PI * atan2(q.x()*q.y() + q.w()*q.z(), 0.5 - q.y()*q.y() - q.z()*q.z());
  float xax  = 180/M_PI * asin(-2.0 * (q.x()*q.z() - q.w()*q.y()));
  float yax    = 180/M_PI * atan2(q.w()*q.x() + q.y()*q.z(), 0.5 - q.x()*q.x() - q.y()*q.y());
  ble.print(F("Orientation: "));
  ble.print(zax);
  ble.print(F(" "));
  ble.print(xax);
  ble.print(F(" "));
  ble.print(yax);
  ble.print(F(" "));
   /* Also send calibration data for each sensor. */
  uint8_t sys, gyro, accel, mag = 0;
  bnoA.getCalibration(&sys, &gyro, &accel, &mag);
  ble.print(sys, DEC);
  ble.print(F(" "));
  ble.print(gyro, DEC);
  ble.print(F(" "));
  ble.print(accel, DEC);
  ble.print(F(" "));
  ble.print(mag, DEC);
  ble.println(F(" "));
 /* bnoB.getEvent(&event);
  imu::Quaternion q2 = bnoB.getQuat();
  ble.print("IMU 2:");
  ble.print(q2.x()); ble.print(", ");
  ble.print(q2.y()); ble.print(", ");
  ble.print(q2.z()); ble.print("\t ");
 displayCalStatusB(); // BNO B
  ble.println(""); */
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
Collapse



new messages
11:10 PM
