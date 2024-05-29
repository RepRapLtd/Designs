//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                          //
//                                     Heltec WiFi Kit 32 NTP Clock                                         //
//                                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Notes:
//
//  "Heltec WiFi Kit 32 NTP Clock" is a ntp initialized date and time clock.  The device connects to the
// an ntp time server via wifi and a udp port, obtains the ntp time from the server, adjusts then writes
// the time to the ESP32 rtc (real time clock), and displays the date and time on the built in OLED display.
//
//  Upon startup, the code initializes the serial port, wifi, graphics and udp port.  The serial port is
// used only during initialization to display when the wifi is connected and when the ntp time has been
// received from the ntp server.  Wifi is used to communicate with the ntp server.  The graphics is used
// to display the initialization and operational displays on the built in OLED.  Finally, the udp port
// receives the ntp time from the ntp server.
//
//  The main loop performs two major functions; obtains the time from the ntp server and to update the oled.
// In this example, the time is obtained from the ntp server only once, and upon receipt, is adjusted for
// time zone then written into the ESP32 rtc (real time clock).  The OLED is updated once per pass, and there
// is a 200ms delay in the main loop so the OLED is updated 5 times a second.
//
//  Before compiling and downloading the code, adjust the following settings:
//
//  1) TIME_ZONE  - currently set to -6 for Oklahoma (my home state), adjust to your timezone.
//  2) chPassword - currently set to "YourWifiPassword", adjust to your wifi password.
//  3) chSSID     - currently set to "YourWifiSsid", adjust to your wifi ssid.
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Includes.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include                              <time.h>                              // for time calculations
#include                              <WiFi.h>                              // for wifi
#include                              <WiFiUdp.h>                           // for udp via wifi
#include                              <U8g2lib.h>                           // see https://github.com/olikraus/u8g2/wiki/u8g2reference

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Constants.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define   FONT_ONE_HEIGHT               8                                   // font one height in pixels
#define   FONT_TWO_HEIGHT               20                                  // font two height in pixels
#define   NTP_DELAY_COUNT               20                                  // delay count for ntp update
#define   NTP_PACKET_LENGTH             48                                  // ntp packet length
#define   TIME_ZONE                     (0)                                // offset from utc
#define   UDP_PORT                      4000                                // UDP listen port

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Variables.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

char      chBuffer[128];                                                    // general purpose character buffer
char      chPassword[] =                  "1Sgdttsa";               // your network password
char      chSSID[] =                      "sew";                   // your network SSID
bool      bTimeReceived =                 false;                            // time has not been received
U8G2_SSD1306_128X64_NONAME_F_HW_I2C       u8g2(U8G2_R0, 16, 15, 4);         // OLED graphics
int       nWifiStatus =                   WL_IDLE_STATUS;                   // wifi status
WiFiUDP   Udp;
                                     
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Setup.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  // Serial.
  
  Serial.begin(115200);
  while(!Serial)
  {
    Serial.print('.');
  }

  // OLED graphics.
  
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
 
  // Wifi.

    // Display title.
    
    u8g2.clearBuffer();
    sprintf(chBuffer, "%s", "Connecting to:");
    u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 0, chBuffer);
    sprintf(chBuffer, "%s", chSSID);
    u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 31 - (FONT_ONE_HEIGHT / 2), chBuffer);
    u8g2.sendBuffer();

    // Connect to wifi.

    Serial.print("NTP clock: connecting to wifi");
    WiFi.begin(chSSID, chPassword);
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    sprintf(chBuffer, "NTP clock: WiFi connected to %s.", chSSID);
    Serial.println(chBuffer);
    
    // Display connection stats.

      // Clean the display buffer.
      
      u8g2.clearBuffer();
  
      // Display the title.

      sprintf(chBuffer, "%s", "WiFi Stats:");
      u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 0, chBuffer);
  
      // Display the ip address assigned by the wifi router.
      
      char  chIp[81];
      WiFi.localIP().toString().toCharArray(chIp, sizeof(chIp) - 1);
      sprintf(chBuffer, "IP  : %s", chIp);
      u8g2.drawStr(0, FONT_ONE_HEIGHT * 2, chBuffer);
  
      // Display the ssid of the wifi router.
      
      sprintf(chBuffer, "SSID: %s", chSSID);
      u8g2.drawStr(0, FONT_ONE_HEIGHT * 3, chBuffer);
  
      // Display the rssi.
      
      sprintf(chBuffer, "RSSI: %d", WiFi.RSSI());
      u8g2.drawStr(0, FONT_ONE_HEIGHT * 4, chBuffer);

      // Display waiting for ntp message.
      
      u8g2.drawStr(0, FONT_ONE_HEIGHT * 6, "Awaiting NTP time...");

      // Now send the display buffer to the OLED.
      
      u8g2.sendBuffer();

  // Udp.
  
  Udp.begin(UDP_PORT);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Main loop.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void  loop()
{
  // Local variables.

  static  int   nNtpDelay = NTP_DELAY_COUNT;
  static  byte  chNtpPacket[NTP_PACKET_LENGTH];

  // Check for time to send ntp request.

  if(bTimeReceived == false)
  {
     // Have yet to receive time from the ntp server, update delay counter.
      
      nNtpDelay += 1;
  
      // Check for time to send ntp request.
      
      if(nNtpDelay >= NTP_DELAY_COUNT)
      {
          // Time to send ntp request, reset delay.
    
          nNtpDelay = 0;
        
          // Send ntp time request.
            
            // Initialize ntp packet.
          
                // Zero out chNtpPacket.
              
                memset(chNtpPacket, 0, NTP_PACKET_LENGTH);
          
                // Set the ll (leap indicator), vvv (version number) and mmm (mode) bits.
                //  
                //  These bits are contained in the first byte of chNtpPacker and are in
                // the following format:  llvvvmmm
                //
                // where:
                //
                //    ll  (leap indicator) = 0
                //    vvv (version number) = 3
                //    mmm (mode)           = 3
                
                chNtpPacket[0]  = 0b00011011;
        
            // Send the ntp packet.
            
            IPAddress ipNtpServer(129, 6, 15, 28);
            Udp.beginPacket(ipNtpServer, 123);
            Udp.write(chNtpPacket, NTP_PACKET_LENGTH);
            Udp.endPacket();

            Serial.println("NTP clock: ntp packet sent to ntp server.");
            Serial.print("NTP clock: awaiting response from ntp server");
      }
      
      Serial.print(".");
      
      // Check for time to check for server response.
    
      if(nNtpDelay == (NTP_DELAY_COUNT - 1))
      {
          // Time to check for a server response.
          
          if(Udp.parsePacket())
          {
              // Server responded, read the packet.
              
              Udp.read(chNtpPacket, NTP_PACKET_LENGTH);
      
              // Obtain the time from the packet, convert to Unix time, and adjust for the time zone.
      
              struct  timeval tvTimeValue = {0, 0};
              
              tvTimeValue.tv_sec = ((unsigned long)chNtpPacket[40] << 24) +       // bits 24 through 31 of ntp time
                                   ((unsigned long)chNtpPacket[41] << 16) +       // bits 16 through 23 of ntp time
                                   ((unsigned long)chNtpPacket[42] <<  8) +       // bits  8 through 15 of ntp time
                                   ((unsigned long)chNtpPacket[43]) -             // bits  0 through  7 of ntp time
                                   (((70UL * 365UL) + 17UL) * 86400UL) +          // ntp to unix conversion
                                   (TIME_ZONE * 3600UL) +                         // time zone adjustment
                                   (5);                                           // transport delay fudge factor
              
              // Set the ESP32 rtc.
              
              settimeofday(& tvTimeValue, NULL);
              
              // Time has been received.
      
              bTimeReceived = true;
              
              // Output date and time to serial.
              
              struct tm * tmPointer = localtime(& tvTimeValue.tv_sec);
              strftime (chBuffer, sizeof(chBuffer), "%a, %d %b %Y %H:%M:%S",  tmPointer);
              Serial.println();
              Serial.print("NTP clock: response received, time written to ESP32 rtc: ");
              Serial.println(chBuffer); 

              // No longer need wifi.

              WiFi.mode(WIFI_OFF);
          }
          else
          {
              // Server did not respond.
              
              Serial.println("NTP clock: packet not received.");
          }
      }
  }
  
  // Update OLED.

  if(bTimeReceived)
  {
      // Ntp time has been received, ajusted and written to the ESP32 rtc, so obtain the time from the ESP32 rtc.
      
      struct  timeval tvTimeValue;
      gettimeofday(& tvTimeValue, NULL);
  
      // Erase the display buffer.
      
      u8g2.clearBuffer();
  
      // Obtain a pointer to local time.
      
      struct tm * tmPointer = localtime(& tvTimeValue.tv_sec);
    
      // Display the date.
  
      strftime(chBuffer, sizeof(chBuffer), "%a, %d %b %Y",  tmPointer);
      u8g2.setFont(u8g2_font_6x10_tr);
      u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 0, chBuffer);
  
      // Display the time.
      
      strftime(chBuffer, sizeof(chBuffer), "%I:%M:%S",  tmPointer);
      u8g2.setFont(u8g2_font_fur20_tn);
      u8g2.drawStr(10, 63 - FONT_TWO_HEIGHT, chBuffer);
  
      // Send the display buffer to the OLED
      
      u8g2.sendBuffer();
  }
    
  // Give up some time.

  delay(200);
}
