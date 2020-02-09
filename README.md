# waterarmy
Firware for a watering plants in my office according their moisture. In this Readme file I'm going to give some details about the prototype and also about the software architecture used on.

![System](http://westial.com/waterarmy/withcovers.jpg)

## Introduction

I have 3 plants in my workspace and there are some periods during year that I cannot water them properly, for vacations, travels, etc. I needed some kind of automated watering system.

Other personal motives were that I'm getting introduced in IoT technologies, and I wanted to learn about LoRa communication. 

## Prototype

![Prototype](http://westial.com/waterarmy/prototype2.jpg)

### Parts and circuit

* 3 moisture sensor.
* 3 12v water pumps. 
* 3 relays.
* 3 potentiometers for moisture setting.
* 2 potentiometers for watering amount setting.
* 1 Arduino Nano.
* USB charger.
* AC 110v to DC 12v power supply converter.
* Wires, board, sprinkles, hoses, soldering stuff,...

![Circuit Schema](http://westial.com/waterarmy/relayedwateringofficeplants_v1.jpg)

### How it works

Every 4h it asks for moisture for every plant. If a plant is under its moisture setting it runs the watering pump according to its watering amount setting.

I included 2 watering amount setting potentiometers only. The first plant it's the biggest one and the one which needs more water. So the first plant is te 100% watering amount, and the other ones take it as a reference to measure their potentiometer values.

## Software architecture

It's composed by two parts: the abstracted use case and the Arduino implementation.

The abstracted use case uses some interfaces to get the business work in the main use case Watering.cpp. This part is located in /waterarmy_lib directory. The component interfaces are available for implementation in the same directory.

The Arduino implementation takes every Watering use case dependency interface and provides its implementation for Arduino Nano. After it injects the dependencies into the use case constructor and invokes it every interval. There is only a little logic in the Arduino loop() method.

## Author

Jaume Mila <jaume@westial.com>
