#include "bc95.h"

bc95 modem;
String apn = "nbiot";
String udpRemoteIP = "13.76.88.107";
int udpRemotePort = 5683;

char* buff = "Hello";
char rxBuffer[512];
long start = 0;
void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(5000);
  Serial.println("Starting");
  modem.init(Serial2);
  modem.reboot();
  Serial.print("#IMEI: ");
  Serial.println(modem.getIMEI());
  delay(5000);
  Serial.print("#IMSI: ");
  Serial.println(modem.getIMSI());
  Serial.print("#Registering NB: ");
  Serial.println(modem.registerNB());
  Serial.println("#Setting APN");
  modem.setAPN(apn);
  Serial.println("#Enabling Packet data: ");
  Serial.println(modem.enableNB());
  Serial.print("#Enabling autoconnect: ");
  Serial.println(modem.enableAutoConnect());
  
  //Initialize CoAP or UDP as required

  //************ Init CoAP to send messages to remote connected device platform ***************************
  Serial.print("#Init CDP: ");
  Serial.println(modem.initCDP("13.76.88.107", 5683, "863703031915296", ""));
  //*******************************************************************************************************
  //************ Open UDP socket to send UDP datagrams ****************************************************
  //Serial.print("#Opening UDP: ");
  //Serial.println(modem.openUDPSocket());
  //*******************************************************************************************************



}


void loop() {

  //***************** if using CoAP************************************
  if (millis() - start > 5000) {
    start = millis();
    Serial.print("Sending CDP Message: ");
    Serial.println(modem.sendCDPMessage(buff, 5));

  }
  memset(rxBuffer, 0, 512);
  if (modem.receiveCDPMessage((char*)rxBuffer) > 0) {
    Serial.println((char*)rxBuffer);
  }
  delay(200);
  //********************************************************************


  //***************if using UDP***************************************
  /* if(millis()-start>5000){
     start=millis();
     modem.sendUDPPacket(udpRemoteIP,udpRemotePort,buff,5);

    }
    bc95::UDPFrame rxFrame=modem.receiveUDPPacket();
    if(rxFrame.length>0){
     Serial.println(rxFrame.data);
    }
  */
  //*********************************************************************

}
