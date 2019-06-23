# Hello World

The classic embedded hello world application is blinking a LED (light emitting diode).
Luckily, the Uno has a built in LED attached to Pin 13, so let's start with blinking that. For now, I'll supply you with the code.

```c
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << DDB5);

    for(;;)
    {
        PORTB |= (1 << PORTB5);
        _delay_ms(500);
        PORTB &= ~(1 << PORTB5);
        _delay_ms(500);
    }
}
```

Don't worry about how it works quite yet. First we need to figure out how to compile it and upload it to the board.

First, create a new working directory and download [this docker-compose file](https://github.com/rubberduck203/avr-template/blob/master/docker-compose.yml)

```bash
mkdir hello-world && cd $_
wget https://raw.githubusercontent.com/rubberduck203/avr-template/master/docker-compose.yml
```

Then start our build tool container with the following command.  
It will automatically mount your current directory inside the container.

```bash
# Don't forget to setup your terminal!
eval $(docker-machine env)
# Start the build tools
docker-compose run --rm buildtools
```

Now that we're inside the running container, let's verify our compiler is available.

```bash
avr-gcc --version
```

This is the cross compiler for the Atmel Atmega 328P on the Arduino.  
We run it on our host (development) machine and it produces machine code for the Atmel AVR architecture. Let's go ahead and compile it. 

```bash
avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
```

There's alot to unpack there, so let's do that.  
This compiles the `hello-world.c` file using all warnings (`-Wall`), optimized for size (`-Os`), for the Atmega 328p processor (`-mmcu=atmega328p`), with a system clock speed of 16MHz (`-DF_CPU=16000000UL`) and outputs the `hello-world.o` *object* file. An object file is an intermediate file that contains all of the information for a single module. Later, it can be linked together with other object files to create an executable.  

We only have a single file, but we can still run the linking process to generate our executable.  

```bash
avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.o -o hello-world.elf
```

This generates an "Executable and Linking Format" file.  
This file is a standard format for *nix executables, but it has extra symbol and debuggin info and isn't appropriate for uploading to our Arduino.  
We need to take one more step to get a file we can upload to our board.

```bash
avr-objcopy -j .text -j .data -O ihex hello-world.elf hello-world.hex
```

The `-j` arguments specify different memory sections, but don't worry about that right now.  
We'll cover that later.  For now, all you need to know is this command turns our *.elf file into one we can upload.  
Speaking of which, let's go ahead and do that!

Arduino's come with a bootloader already burned into their memory.  
We're going to leverage that and use [avrdude](https://www.nongnu.org/avrdude/) to upload the program.  
Not all processors come with a bootloader installed.  
Often, we'll need to use special purpose hardware, called a programmer, to directly burn programs to memory, but we'll just stick to the bootloader since we have it available to us.

```bash
avrdude -v -patmega328p -carduino -b115200 -D -Uflash:w:hello-world.hex:i
```

This uploads to an Atmega 328p process, using the Arduino bootloader, at a baud rate of 115200 bits/s, deletes the flash prior to uploading, then uploads our hex file to the flash memory on the target device.

If all went well, you should the built-in led flashing on and off every half second!
Congratulations!

[Prev](./00-intro.md)
[Next](./02-hello-world-explained.md)
