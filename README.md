# About

Ludiac is a literacy support system for children with ADHD.

Contemplates a [virtual reality game](https://github.com/LeomaiaJr/Ludiac-Game) with cartoon-like scenarios, where the child will go through a series of playful exercises and learn mathematics or grammar. The game is controlled by the position (down or up) of two sticks.

Project developed during PROJETE – Technological Projects Fair of Francisco Moreira da Costa Technical School of Electronics, during the last year (2021) of the System Development Technical Course.

# Firmware

Components:

- Node MCU ESP8266
- 2x SW-200D

Node MCU sends all the data from the reading of the SW-200D sensors to the game using socket comunication.

First it:

1. Connects to Wifi
2. Open Socket server
3. Send data to clients
