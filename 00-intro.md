# What is Embedded Software?

Embedded software is software that's been embedded into a product.  
That's it.  That's all there is to it.  
This covers a huge range of different development targets.  

From 8-bit microcontrollers in TV remotes

[![LG television remote](https://upload.wikimedia.org/wikipedia/commons/thumb/4/4d/LG_IR_TV_Remote_Control_AKB74475418.jpg/135px-LG_IR_TV_Remote_Control_AKB74475418.jpg)](https://commons.wikimedia.org/wiki/File:LG_IR_TV_Remote_Control_AKB74475418.jpg)

To Smart Televisions running Linux

[![LG WebOS](https://upload.wikimedia.org/wikipedia/en/e/ec/LG_webOS.jpg)](https://en.wikipedia.org/wiki/WebOS)

To the Mars Pathfinder Rover running Real Time Operating Systems

[![Mars Pathfinder Rover](https://www.jpl.nasa.gov/spaceimages/images/wallpaper/PIA01122-800x600.jpg)](https://www.jpl.nasa.gov/spaceimages/details.php?id=PIA01122)

All of these systems have embedded software in them and they have one thing in common, they're not general purpose computing machines.  
The software they run is purpose built for the hardware they run on to do one particular thing.  
Consumers aren't setting out to buy a computer or software, they're buying a product that happens to have software in it.  
They're buying a television, or refrigerator, or car, not your software.

## The Matrix

Embedded software comes in many forms, but it's really more of a matrix than a simple spectrum.  

### Embedded Operating Systems

The easiest distinction to make is what kind, if any, operating system we're running on.

### "Traditional" OS

This is software that is running on a traditional operating system, like Linux, Window, Android, or iOS.  

Examples include:
 - Automobile infotainment systems
 - Smart televisions
 - In store kiosks
 - Hobby projects using Raspberry Pi

This environment is the most like the development most of us are accustomed to and, while there are special considerations to be made for these when embedding in a product, we won't cover these because they're the easiest embedded environments to transition to. 

### Real Time Operating Systems (RTOS)

Real Time operating systems are often used safety critical applications, but can also be useful in very complex applications. They typically provide a task scheduler and some level of memory protection and separation between the kernal and user space.

While these are called "real time" systems, that's a bit of a misnomer.  They should really be called *Deterministic* operating systems. They provide the programmer with guarantees about maximum execution times within the system, often necessary for safety critical applications.

There are many different open and proprietary RTOS out there, like QNX and FreeRTOS, but we'll not cover this topic any further either, as I don't feel it's necessary for a beginner to get started with embedded development.

### Bare Metal

Here, there is no operating system.  
We're directly responsible for interacting with the hardware.
This is what most people are thinking of when they ask me about embedded software, and possibly the hardest to get started with on your own.  
Therefore, this will be the topic of the rest of the book.

[Next](./01-hello-world.md)