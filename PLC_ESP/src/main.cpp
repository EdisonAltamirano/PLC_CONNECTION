#include <Arduino.h>
// #include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

// //needed for library
// #include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
// #include <esp_wifi.h>

// #include <ModbusIP_ESP8266.h>

// //////Modbus//////
// IPAddress remote(10, 22, 231, 238); // Address of Modbus Slave device
// const int OUTPUTCOUNTOUT = 30;
// int OUTPUTOFFSETOUT = 30;
// uint16_t resoutputsout[OUTPUTCOUNTOUT];
// uint16_t finalarray[OUTPUTCOUNTOUT];
// ModbusIP mb; // ModbusIP object
// //Funcion para enviar datos
// bool cbinputs(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
//   if (event != Modbus::EX_SUCCESS)                  // If transaction got an error
//     Serial.printf("Modbus result: %02X\n", event);  // Display Modbus error code
//   if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
//     mb.disconnect(remote);              // Close connection to slave and
//     mb.dropTransactions();              // Cancel all waiting transactions
//   }
//   if(event == Modbus::EX_SUCCESS)  {
//     Serial.println("write outputs");
//   }
//   return true;
// }

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // finalarray[0] = 3;
  
  // // // put your main code here, to run repeatedly:
  // if(!mb.writeHreg(remote, OUTPUTOFFSETOUT, finalarray, OUTPUTCOUNTOUT, cbinputs)){ // Try to Write array of COUNT of Coils to Modbus Slave
  //   Serial.print("#");
  // }
}