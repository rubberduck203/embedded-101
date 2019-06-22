# Summary

Over the last year, I've been asked the same question over and over again.

> How do I get started with embedded software development?

I usually tell people to go buy an Arduino, throw away the Arduino IDE and libraries, and figure out how to blink a light using just the AVR toolchain.  
This "book" is designed to teach you how to do exactly that, and then move on to the other basics of embedded software dev that you need to know to start your journey.

## Prerequisites

As an introduction, this "course" requires no prior knowledge of embedded software, C, or C++, or electronics, but does assume a general knowledge of programming in general.

### Hardware

For this course, we'll use an
[Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3/)
because of its ubiquity and availability.
Feel free to purchase a clone, personally, I like the [SparkFun Redboard](https://www.sparkfun.com/products/13975), but many different Uno clones are available for as little as $10.
You'll also need a small breadboard, some jumpers, leds, resistors, capacitors, buttons, and other odds and ends to get the most out of this.  
I recommend something like [Adafruit's Parts Pal](https://www.adafruit.com/product/2975) kit or [SparkFun's Beginners Parts Kit](https://www.sparkfun.com/products/13973) and [Half Sized Breadboard](https://www.sparkfun.com/products/12002).  
We're not going to cover electronics at any depth, but we will need to wire up a few simple circuits.

#### Datasheets

- [Atmega328p](http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf)
- [Sparkfun Redboard](https://cdn.sparkfun.com/assets/1/3/5/9/6/Redboardv2.pdf)

### Software

For my own projects, I've developed a [Docker image for AVR development](https://hub.docker.com/r/rubberduck/avr).  
It contains the AVR toolchain and relevant software you'll need.  

If you're running Linux, you need no additional setup, beyond some configuration files to tell `avrdude` and `minicom` which serial port your board is attached to.

#### Install tools on Mac via Homebrew

This is the recommended way of installing the tools on OS X.
For some people the docker setup below works fine, for others, VirtualBox can't see the USB device.
For that reason, I highly recommend you just use Homebrew to install the AVR toolchain.

Be advised that compiling & installing the compilers can take quite some time.

```bash
brew tap osx-cross/avr
brew install \
    avr-gcc \
    avrdude \
    minicom \
    cpputest \
    pkg-config \
    gcc
```

#### Using the docker image on Mac

For reasons you can read about on my blog if you care, [connecting a docker container to USB ports on Mac](https://christopherjmcclellan.wordpress.com/2019/04/21/using-usb-with-docker-for-mac/) requires a bit more software and setup.

- Download and Install [VirtualBox 6.06](https://www.virtualbox.org/wiki/Downloads) or greater.
  - You MUST have version 6.06 or greater, there was a bug in earlier versions that cause this to fail.
- Download and install the [VirtualBox extension pack](https://download.virtualbox.org/virtualbox/6.0.6/Oracle_VM_VirtualBox_Extension_Pack-6.0.6.vbox-extpack)
- Download and run the [mac-setup-docker.sh](mac-setup-docker.sh) script.
- Setup your terminal by running `eval $(docker-machine env)`
  - You'll need to run this each time you create a new terminal, or add it to your profile.

## Table of Contents

 - [Introduction: What is Embedded Software?](./00-intro.md)
 - [Hello World](./01-hello-world.md)
 - [Hello World Explained](./02-hello-world-explained.md)
 - [Exercise: Offboard LEDs](./03-offboard-leds.md)
   - Breadboards, LEDs, schematics, more datasheets
 - Make
   - Basics
   - AVR Template
 - Interrupts (Turn light on/off with a push button)
   - Bouncing
   - Intro to Logic Analyzer
 - Timers
 - Unit Testing
 - Integration Testing
 - Pulse Width Modulation (PWM)
 - Analog Digital Conversion (ADC)
 - Serial Communications
   - UART
   - SPI
   - I2C
   - CAN
   - Modbus


## License

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.

Addititionally, all code in this repository is licensed under the MIT license.

```txt
MIT License

Copyright (c) 2019 Christopher J. McClellan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
