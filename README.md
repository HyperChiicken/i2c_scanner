# i2c_scanner
Scan for your i2c device's slave address; yes

I had some parts lying around, and I wanted to give them some purpose. So I went ahead and pimped my breadboard with an i2c scanner. The scanner basically looks for the device's slave address then displays it on the LCD screen. This makes it easier to find the address without diving into the datasheet. I still suggest  CTRL+F the displayed slave address within the datasheet to confirm. 
For this project, 

I cobbled the following parts together:
* barebones MSP430 (M430G2553) 
* 20x4 LCD screen
* breadboard

## The Steps
It's important to test things out before soldering and mounting things together. So I started out by wiring connections to their respective ports (as seen on the schematics posted), then uploaded the code onto the MSP430 devboard using Energia (TI's fork of the Arduino IDE).
Once it's working properly, I did the following:
1) I soldered my rendition of a MSP430 barebones board. It's definitely missing some parts like decoupling capacitors and whatnot, but it works.
2) Mounted the LCD to the stand.
3) Mounted the LCD combo to the breadboard.
4) Wired up the connections.

I encountered some problems where the was code working with the devboard but not with the barebones board. To fix it, I needed to modify the boards.txt found in C:\Users\yourusername\AppData\Local\Energia15\packages\energia\hardware\msp430\1.0.3. The directory can be different in your system. 
I don't quite remember what I changed but here's what I have for the M430G2553 in boards.txt:
```
#MSP-EXP430G2553
  
MSP-EXP430G2553LP.vid.0=0x2341
MSP-EXP430G2553LP.pid.0=0x0c9f
  
MSP-EXP430G2553LP.name=MSP-EXP430G2 w/ MSP430G2553
  
MSP-EXP430G2553LP.build.mcu=msp430g2553
MSP-EXP430G2553LP.build.f_cpu=16000000L
MSP-EXP430G2553LP.build.core=msp430
MSP-EXP430G2553LP.build.variant=MSP-EXP430G2553LP
MSP-EXP430G2553LP.build.board=MSP_EXP430G2553LP
MSP-EXP430G2553LP.build.extra_flags=
  
MSP-EXP430G2553LP.upload.tool=mspdebug
MSP-EXP430G2553LP.upload.protocol=rf2500
MSP-EXP430G2553LP.upload.maximum_size=16384
MSP-EXP430G2553LP.upload.maximum_data_size=512
```

Caveats: One thing I noticed is that the scanner returns a random HEX when the device is not hooked up properly.The same is true when nothing is plugged in. This can be mitigated by adding more code to catch the error then display that error message.

Checkout for more details: https://www.hackster.io/HyperChiicken/i2c-scanner-eac1cb
