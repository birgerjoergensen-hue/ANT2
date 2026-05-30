Run REAL_FQBN="adafruit:nrf52:feather52840sense"
/home/runner/work/ANT2/ANT2/ANT2.ino: In function 'void setup()':
/home/runner/work/ANT2/ANT2/ANT2.ino:82:36: error: no matching function for call to 'BLESecurity::setIOCaps(int)'
   82 |   Bluefruit.Security.setIOCaps(0x03);
      |                                    ^
In file included from /home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/Bluefruit52Lib/src/bluefruit.h:58,
                 from /home/runner/work/ANT2/ANT2/ANT2.ino:5:
/home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/Bluefruit52Lib/src/BLESecurity.h:51:10: note: candidate: 'void BLESecurity::setIOCaps(bool, bool, bool)'
   51 |     void setIOCaps(bool display, bool yes_no, bool keyboard);
      |          ^~~~~~~~~
/home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/Bluefruit52Lib/src/BLESecurity.h:51:10: note:   candidate expects 3 arguments, 1 provided

Error during build: exit status 1

Used library                                     Version Path                                                                                             
Adafruit Bluefruit nRF52 Libraries               0.21.0  /home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/Bluefruit52Lib          
Adafruit nRFCrypto                               0.1.2   /home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/Adafruit_nRFCrypto      
Adafruit TinyUSB Library                         3.6.0   /home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/Adafruit_TinyUSB_Arduino
SPI                                              1.0     /home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/SPI                     
Adafruit Little File System Libraries            0.11.0  /home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/Adafruit_LittleFS       
Adafruit Internal File System on Bluefruit nRF52 0.11.0  /home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0/libraries/InternalFileSytem       

Used platform  Version Path                                                          
adafruit:nrf52 1.7.0   /home/runner/.arduino15/packages/adafruit/hardware/nrf52/1.7.0
Error: Process completed with exit code 1.
