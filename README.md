# waterarmy
Firware for a watering plants in my office according their moisture. In this Readme file I'm going to give some details about the prototype and also about the software architecture used on.

![System](http://westial.com/waterarmy/withcovers.jpg)

## Introduction

I have 3 plants in my workspace and there are some periods during year that I cannot water them properly, for vacations, travels, etc. I needed some kind of automated watering system.

Other personal motives were that I'm getting introduced in IoT technologies, and I wanted to learn about LoRa communication. 

## Prototype

![Prototype](http://westial.com/waterarmy/prototype2.jpg)

### Parts and circuit

* 3 moisture sensor. [OSOYOO moisture sensor](https://osoyoo.com/2018/04/29/use-arduino-to-detect-soil-moisture-and-display-daga-in-16x2-lcd/).
* 3 12v water pumps. [Amazon JP item](https://www.amazon.co.jp/gp/product/B06XYC54XR/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
* 3 relays. [OSOYOO relay](https://osoyoo.com/2017/08/28/arduino-lesson-1-channel-relay-module/)
* 3 100Ω potentiometers for moisture setting. [Amazon JP item](https://www.amazon.co.jp/gp/product/B01MG0XKPQ/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1)
* 2 100Ω potentiometers for watering amount setting.
* 1 Arduino Nano. [Amazon JP item](https://www.amazon.co.jp/gp/product/B01F741W6O/ref=ppx_yo_dt_b_asin_title_o08_s00?ie=UTF8&psc=1)
* 1 Arduino Nano. [OSOYOO LoRa module](https://osoyoo.com/2018/07/26/osoyoo-lora-tutorial-how-to-use-the-uart-lora-module-with-arduino/)
* USB charger plug. You can find anywhere.
* AC 110v to DC 12v power supply converter. I recicled from my old router.
* Wires, board, sprinkles, hoses, soldering stuff,...

![Circuit Schema](http://westial.com/waterarmy/relayedwateringofficeplants_v1.jpg)

### How it works

Every 4h it asks for moisture for every plant. If a plant is under its moisture setting it runs the watering pump according to its watering amount setting.

I included 2 watering amount setting potentiometers only. The first plant it's the biggest one and the one which needs more water. So the first plant is te 100% watering amount, and the other ones take it as a reference to measure their potentiometer values.

## Software architecture

It's composed by two parts: the abstracted use case and the Arduino implementation.

The abstracted use case uses some interfaces to get the business work in the main use case Watering.cpp. This part is located in /waterarmy_lib directory. The component interfaces are available for implementation in the same directory.

The Arduino implementation takes every Watering use case dependency interface and provides its implementation for Arduino Nano. After it injects the dependencies into the use case constructor and invokes it every interval. There is only a little logic in the Arduino loop() method.

### Cloud logging

I used LoRa device to send the moisture readings and the watering amount settings to the cloud.

![Log](http://westial.com/waterarmy/wateringlog.png)

* The LoRa serial communication transmits some bytes through low radio to another LoRa device installed on a RaspberryPi. 
* The RaspberryPi is connected by wire to internet, converts the bytes into a request to record a metric into AWS CloudWatch. 
* I configured the  dashboard with the history chart of them and also some Alarms to get noticed when something unexpected is happening.

You can find the very basic script installed on RaspberryPi as a service in /rpilora_service.

![Log](http://westial.com/waterarmy/rpilora.jpg)

## Author

Jaume Mila 
<[jaume@westial.com](mailto:jaume@westial.com)>
