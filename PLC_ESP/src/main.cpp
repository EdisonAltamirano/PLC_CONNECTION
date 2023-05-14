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
//INPUTS GPIOs 
const int num_inputs = 12;
const int inputs[num_inputs] = {36,39,34,35,32,33,25,26,27,14,12,13};
//OUTPUTS GPIOs 
const int num_outputs = 13;
const int outputs[num_outputs] = {23,22,1,3,21,19,18,5,17,16,4,2,15};
uint16_t resoutputsout[num_outputs];
// //////Modbus///p///
IPAddress remote(192, 168, 74, 59); // Address of Modbus Slave device
int OUTPUTCOUNT = 30;
int OUTPUTOFFSET = 30;
int INPUTCOUNT = 30;
int INPUTOFFSET = 0;
uint16_t finalarray[500] = {0};
ModbusIP mb; // ModbusIP object
// Funcion para enviar datos
bool cboutputs(Modbus::ResultCode event, uint16_t transactionId, void *data)
{                                                  // Modbus Transaction callback
  if (event != Modbus::EX_SUCCESS)                 // If transaction got an error
    Serial.printf("Modbus result: %02X\n", event); // Display Modbus error code
  if (event == Modbus::EX_TIMEOUT)
  { // If Transaction timeout took place
    Serial.println("Timeout");
    mb.disconnect(remote); // Close connection to slave and
    mb.dropTransactions(); // Cancel all waiting transactions
  }
  if (event == Modbus::EX_SUCCESS)
  {
    Serial.println("write outputs");
  }
  return true;
}
bool res = false;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i = 0; i < num_inputs; i++)
  {
    pinMode(inputs[i],INPUT_PULLUP);
  }
  for (int j = 0; j < num_outputs; j++)
  {
    pinMode(outputs[j],OUTPUT);
  }
  

  // WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  res = wm.autoConnect("testesp32_2"); // password protected ap

  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
}
bool cboutputsregisters(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  if (event != Modbus::EX_SUCCESS)                  // If transaction got an error
    Serial.printf("Modbus result1: %02X\n", event);  // Display Modbus error code
  if (event == Modbus::EX_TIMEOUT) {    // If Transaction timeout took place
    mb.disconnect(remote);              // Close connection to slave and
    mb.dropTransactions();              // Cancel all waiting transactions
  }
  if(event == Modbus::EX_SUCCESS)  {
    int count_outfinal = 0;
    for(int i=0;i<=num_outputs;i++){
      count_outfinal = INPUTOFFSET + i;
      finalarray[count_outfinal] = resoutputsout[i];
    }
  }
  return true;
}

void loop()
{
  finalarray[0] = 3;
  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    if (mb.isConnected(remote))
    {
      Serial.println("connected...yeey :)");
     
      int count_infinal = 0;
      for (int i = 0; i < num_inputs; i++)
      {
        count_infinal = OUTPUTOFFSET + i;
        finalarray[count_infinal] = digitalRead(inputs[i]);
      }
      uint16_t outputarray[OUTPUTCOUNT] = {0};
      int count_out = 0;
      for (int i = OUTPUTOFFSET; i < OUTPUTCOUNT; i++)
      {
        outputarray[count_out] = finalarray[i];
        count_out++;
      }
      // Enviar inputs de ESP a PLC
      if (!mb.writeHreg(remote, OUTPUTOFFSET, finalarray, OUTPUTCOUNT, cboutputs))
      {
        Serial.print("|");
      }
      // Recibir outputs de PLC a ESP
      mb.readHreg(remote, INPUTOFFSET,resoutputsout,num_outputs,cboutputsregisters);
      int count_outfinal = 0;
      for (int i = 0; i < num_outputs; i++)
      {
        count_outfinal = INPUTOFFSET + i;
        (finalarray[count_outfinal] == HIGH) ? digitalWrite(outputs[i], HIGH) : digitalWrite(outputs[i], LOW);
      }
      
    }
    else
    {
      Serial.print('*');
      mb.connect(remote);
    }
    mb.task();
    delay(100);
  }
}