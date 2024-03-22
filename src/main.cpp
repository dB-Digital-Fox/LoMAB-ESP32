#include <Arduino.h>
#include <lora.h>

#define RFM_CS 27 //chipselect pin, MISO
#define RFM_RST 23 //reset pin, RST
#define RFM_INT 19 //interrupt pin , MOSI

#define BUFFER_LEN 20
#define APP_DATA_LEN 7

lora lorafiit(RFM_CS, RFM_INT, RFM_RST);

void setup() {
  Serial.flush();
  while(!Serial);
  Serial.begin(115200);//Sets Baud rate
  Serial.flush();
  delay(100);

  uint8_t buffer[BUFFER_LEN];
  uint8_t sizeOfBuffer = BUFFER_LEN;

  lorafiit.On();

  while (!lorafiit.Register(buffer, sizeOfBuffer)) {
    #if SERIAL_DEBUG
      Serial.println(F("Registration not successfull."));
    #endif
  }

  #if SERIAL_DEBUG
    // Serial.println(rtc.millis());
    Serial.println(F("Registration successful, netconfig recieved"));
  #endif
}

void loop() {

  uint8_t appData[APP_DATA_LEN] = "B5BBBB"; //user application data
  uint8_t sizeOfAppData = APP_DATA_LEN; //size in B

  delay(10000);

  if (lorafiit.Send(TYPE_DATA_UP, ACK_MAN, appData, sizeOfAppData)) {
    #if SERIAL_DEBUG
      Serial.println(F("Message with ACK has been sent"));
    #endif
  }
}
 