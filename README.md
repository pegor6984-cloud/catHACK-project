# catZERO-project
```text
 ██████╗ █████╗ ████████╗███████╗███████╗██████╗  ██████╗
██╔════╝██╔══██╗╚══██╔══╝╚══███╔╝██╔════╝██╔══██╗██╔═══██╗
██║     ███████║   ██║     ███╔╝ █████╗  ██████╔╝██║   ██║
██║     ██╔══██║   ██║    ███╔╝  ██╔══╝  ██╔══██╗██║   ██║
╚██████╗██║  ██║   ██║   ███████╗███████╗██║  ██║╚██████╔╝
 ╚═════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚══════╝╚═╝  ╚═╝ ╚═════╝
```
Hello my name is Egor I'm 13 I live in Germany I created my new catZERO project on ESP32-S3.Based on this project, ESP32-S3 Super Mini is used.I made some changes to the program and now there is an SD card lift.And now a control console has appeared there, but it is not quite completed.Due to a lack of pins for the SD card, we had to use a new technique for connecting clock buttons to the board.Now all the buttons are connected via resistors to one pin and everything works fine
Now a Wi-Fi chat has been added. If you are connected to Wi-Fi and you go to the IP address that the program gave you, then you can chat from device to device. Then a battery calculation was added. If you use exactly the same battery calculation as mine. To be more precise, 650 mah And if you have a different battery calculation, then you can set this in the program I have done such a great job so please can any of you promote me Был улучшен nrf Jammer но он всё равно плохо работает и был лучшим TV-B-Gone теперь он реально может включать и выключать телевизоры
Sorry for the fact that I was gone for so long the project has undergone very big changes now We have switched to a new processor Sorry that it is more expensive but now there are more functions We have switched to the ESP32 S3 Super Mini raft a new module has been added that's all CC1101 SD card module circuit diagrams I will now post and now a new command will appear firstly for CC1101 and working Bad USB scripts have appeared
And now there are two new RGB LEDs, one we place under the keyboard, our navigation buttons, and the second I use as a piece of LED strip for eight RGB LEDs
In the meantime, I’ve tried adding a lot of new things; first of all, I attempted to create an improved Deauther and Evil Portal.I also improved the jammer, but it still isn't working—even though I tried porting that function over from the Bruce firmware. Then I created a new "Apps" section; it now includes a calculator, two games, and Wikipedia. Now, when you connect to Wi-Fi, you can access Wikipedia, type in a question, and get an answer from the site. But in reality, everything else remains unchanged.
I also spent a great deal of time working with a library U8g2 for Cyrillic support—since I’m from Ukraine, I’m familiar with Russian and other languages ​​that use the Cyrillic script. I tried to get two libraries working simultaneously: one handling rendering and the Wi-Fi chat, and another managing Wikipedia integration, so that Russian text could be displayed.
But in the end, nothing worked out for me, so guys, I’m really asking for your help.Hello, my dear viewers. I am finally ready to present the Cat Zero 2.1.5 firmware to you. It includes a lot of new features; first of all, there is now a launcher—a GitHub repository with a fully ready-to-use launcher is coming soon, but there is already a built-in, fully functional launcher. Support for RFID tags has also been added, meaning it now supports modules such as the PN532 and RC522 There is also a new airfit menu, it has module settings, usage protocol and pinout, the firmware is now being actively improved. Sorry because in this code there are a lot of different crutches, some kind of stubs, and so on, but soon I will try to fix it all, firstly with the rc522 module, you can scan the service marks then with the pn532 module. Is it possible to scan and emulate, maybe the emulation is not so accurate, but soon I will fix it, it still works now active work on a file manager where it will be possible to move the built-in memory from an SD card, you can copy it, delete it, and so on, we are working on a new one and A new firmware version will be released soon, so stay tuned for updates.New GPIO pins have appeared, and while they could potentially be used in other ways, for the time being, they are used for interfacing with R-Fit modules.There is also a new Apps menu, it has games and Wikipedia when the Internet is connected. You can ask questions on Wikipedia. Then badUSB scripts appeared,There are also many new features; I’ll try to describe them all soon, and for now, I’m posting the new code.We’ve also started working on Bluetooth support, though—I apologize—progress is currently slow because there are other, newer, and more interesting ideas taking priority. However, if you’d like, I can begin full-scale development on Bluetooth features—such as BADBLE.

This code included an Internet connection and a beautiful Internet icon when connected to it

Connectio:

buzzer:

gnd-gnd

vcc-3D

rgd (Keyboard):

vcc-5v

gnd-gnd

in-16

rgb (BOARD):

vcc-5v

gnd-gnd

in-14

oled(128x64):

gnd-gnd

vcc-5v

scl-9D

sda-8D

button(reset):
reset-1D

buttons:

3.3V
 
 |

[3.3k] ← tightening
 
 |
 
 +-------> GPIO17 (for testing; can be replaced later)
 
 |
 
 +--[2.2k]----Up button----GND
 
 |
 
 +--[3.3k]--Down Button-----GND
 
 |
 
 +--[6.8k]---OK button-------GND

nrf24:

CE-11D

CSN-10D

MOSI-7D

SCK-6D

MISO-2D

Ir capture/transmit:

capture:

gnd-gnd

vcc-vcc

s-5D

transmit:

gnd-gnd

vcc-18D

mikro sd 

gnd-gnd

vcc-3.3v

cs-20D

mosi-7D

miso-2D

cls-6D

CatHACK Features:

WIFI:

Scan

spectrum

Wi-fi chat

deuther

evil portal

bluetooth:

scan

nRF24:

Spectrum

jammer

Recheck

IR:

capture

transmit

Erase All

TV-B-Gone

console:

As I already said, it will be possible to transport different teams there
There is also a secret panel and you can change the code for it in the program

Settings:

info

Timeout

Reset

Reboot

CC1101:

spectrum (vert)

spectrum (horiz)

jammer

capture

transmit

storager:

The file manager function isn't working yet; selecting it causes the device to reboot. Please do not use this feature for the time being, as it will restart your device. I apologize for the inconvenience and will fix this issue soon.

launcher:

As soon as you select this menu, you enter the launcher, where you can install firmware from an SD card (as a .bin file); at the very end, there is a button to return to the standard menu.

apps:

audio

dino

Bird

Wikipedia

rfid:

config

scan

emulate


That's all for now, now I'll sit and improve my code!!

(Guys, I was afraid of hate and that's why I renamed my project to catZero!!!)
