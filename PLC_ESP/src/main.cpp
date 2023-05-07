#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiManager.h>
#include <ModbusIP_ESP8266.h>
// //needed for library
// #include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
// #include <esp_wifi.h>

// #include <ModbusIP_ESP8266.h>

// //////Modbus///p///
IPAddress remote(10, 22, 231, 238); // Address of Modbus Slave device
const int OUTPUTCOUNTOUT = 30;
int OUTPUTOFFSETOUT = 30;
uint16_t resoutputsout[OUTPUTCOUNTOUT];
uint16_t finalarray[OUTPUTCOUNTOUT];
ModbusIP mb; // ModbusIP object
//Funcion para enviar datos
bool cbinputs(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Modbus Transaction callback
  if (event != Modbus::EX_SUCCESS)                  // If transaction got an error
    Serial.printf("Modbus result: %02X\n", event);  // Display Modbus error code
  if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
    mb.disconnect(remote);              // Close connection to slave and
    mb.dropTransactions();              // Cancel all waiting transactions
  }
  if(event == Modbus::EX_SUCCESS)  {
    Serial.println("write outputs");
  }
  return true;
}
  bool res=false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    
  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;
  // put your setup code here, to run once:
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("testesp32"); // password protected ap

  if(!res) {
      Serial.println("Failed to connect");
      // ESP.restart();
  } 
  else {
      //if you get here you have connected to the WiFi    
      Serial.println("connected...yeey :)");
  }

}


void loop() {
  // finalarray[0] = 3;
  // if(!res) {
  //     Serial.println("Failed to connect");
  //     // ESP.restart();
  // } 
  // else {
  //     //if you get here you have connected to the WiFi    
  //     Serial.println("connected...yeey :)");
  // }
  // // // put your main code here, to run repeatedly:
  // if(!mb.writeHreg(remote, OUTPUTOFFSETOUT, finalarray, OUTPUTCOUNTOUT, cbinputs)){ // Try to Write array of COUNT of Coils to Modbus Slave
  //   Serial.print("#");
  // }
}