# Summary

Over the last year, I've been asked the same question over and over again.

> How do I get started with embedded software development?

I usually tell people to go buy an Arduino, throw away the Arduino IDE and libraries, and figure out how to blink a light using just the AVR toolchain.  
This "book" is designed to teach you how to do exactly that, and then move on to the other basics of embedded software dev that you need to know to start your journey.

## Prerequisites

As an introduction, this "course" requires no prior knowledge of embedded software, C, or C++, or electronics, but does assume a general knowledge of programming in general.

### Hardware

For this course, we'll use an [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3/) because of it's ubuity and availability.  
Feel free to purchase a clone, personally, I like the [SparkFun Redboard](https://www.sparkfun.com/products/13975), but many different Uno clones are available for as little as $10.
You'll also need a small breadboard, some jumpers, leds, resistors, capacitors, buttons, and other odds and ends to get the most out of this.  
I recommend something like [Adafruit's Parts Pal](https://www.adafruit.com/product/2975) kit or [SparkFun's Beginners Parts Kit](https://www.sparkfun.com/products/13973) and [Half Sized Breadboard](https://www.sparkfun.com/products/12002).  
We're not going to cover electronics at any depth, but we will need to wire up a few simple circuits.

### Software

For my own projects, I've developed a [Docker image for AVR development](https://hub.docker.com/r/rubberduck/avr).  
It contains the AVR toolchain and relevant software you'll need.  

If you're running Linux, you need no additional setup, beyond some configuration files to tell `avrdude` and `minicom` which serial port your board is attached to.

#### Using the docker image on Mac

For reasons you can read about on my blog if you care, [connecting a docker container to USB ports on Mac](https://christopherjmcclellan.wordpress.com/2019/04/21/using-usb-with-docker-for-mac/) requires a bit more software and setup.

- Download and Install [VirtualBox 6.06](https://www.virtualbox.org/wiki/Downloads) or greater.
  - You MUST have version 6.06 or greater, there was a bug in earlier versions that cause this to fail.
- Download and install the [VirtualBox extension pack](https://download.virtualbox.org/virtualbox/6.0.6/Oracle_VM_VirtualBox_Extension_Pack-6.0.6.vbox-extpack)
- Download and run the [mac-setup-docker.sh](mac-setup-docker.sh) script.
- Setup your terminal by running `eval $(docker-machine env)`
  - You'll need to run this each time you create a new terminal, or add it to your profile.

#### Install tools on Mac via Homebrew

Sometimes the docker setup can be a bit flaky in regards to usb, so if you want to just install the tools, you can use Homebrew.
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

## Table of Contents

 - [Introduction: What is Embedded Software?](./00-intro.md)
 - [Hello World](./01-hello-world.md)
 - [Hello World Explained](./02-hello-world-explained.md)
 - Make
   - Basics
   - AVR Template
 - Offboard LED
   - Breadboards, LEDs, schematics, more datasheets
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
