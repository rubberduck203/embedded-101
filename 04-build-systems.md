# Build Systems

Let's revisit our build commands from [the hello world example](./01-hello-world.md).

```bash
avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.o -o hello-world.elf
avr-objcopy -j .text -j .data -O ihex hello-world.elf hello-world.hex
```

This is a bit tedious to execute each time we edit the `*.c` file.
Any time we find ourselves repeatedly doing the same thing, our instinct should be to automate it.
We could easily put this in a shell script (here named `build.sh`).

```bash
#! /usr/bin/env bash -ex

avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.o -o hello-world.elf
avr-objcopy -j .text -j .data -O ihex hello-world.elf hello-world.hex
```

Once we make this script executable

```bash
chmod +x build.sh
```

We can then execute it to build our executable.

```console
rubberduck@pond:~/hello-world$ ./build.sh 
+ avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
+ avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.o -o hello-world.elf
+ avr-objcopy -j .text -j .data -O ihex hello-world.elf hello-world.hex
```

This works well for our small program, but if you execute the build again,  
you'll see one of this approach's big weaknesses.

```console
rubberduck@pond:~/hello-world$ ./build.sh 
+ avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
+ avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.o -o hello-world.elf
+ avr-objcopy -j .text -j .data -O ihex hello-world.elf hello-world.hex
```

The shell script approach will compile every file each time we run the build.  
This isn't a problem for our small program, but isn't something we would want for a large program with many files.  
We want it to be quick to compile our program, so we only want to compile the file sthat have actually changed.  
This is called an _incremental build_.

There are many different build systems to help us solve the incremental build problem, among them `Make`, `CMake`, `Autotools`, and others.  
`Make` is probably the simplest build system I know of (in fact, `CMake` generates `makefiles`), so we'll use it here as an example, but I encourage you to research your options.

## Make

In the `hello-world` directory, create a new file named `makefile` and then run it.

```console
rubberduck@pond:~/hello-world$ touch makefile
rubberduck@pond:~/hello-world$ make
make: *** No targets.  Stop.
```

Okay, so let's add our first target to the file.  
In `makefile`s, we specify the _target_ on the left of the colon and the _preresequites_ on the right.

```make
target-file: preresequites
```

Since we first need to compile our `hello-world.c` file into an object file, let's start by creating a target for `hello-world.o` and a _rule_ for creating it.

```make
hello-world.o: hello-world.c
	avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
```

Note that you ***MUST*** use tabs to indent in make.  
If you're getting errors, make sure it's indented with a single tab.

Now, if we execute the `make` command, you'll see the rule gets executed and our object file gets created.

```console
rubberduck@pond:~/hello-world $ make
avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
rubberduck@pond:~/hello-world $ ls *.o
hello-world.o
```

And if we execute it again, you'll see that Make knows we've not modified the code file.

```console
rubberduck@pond:~/hello-world $ make
make: `hello-world.o' is up to date.
```

But if we modify `hello-world.c`, Make will detect it and re-compile the file.

```console
rubberduck@pond:~/hello-world $ touch hello-world.c && make
avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
```

So we've demonstrated Make's incremental build capabilities, now let's fill in the rest of our compilation steps.

```makefile
hello-world.hex: hello-world.elf
	avr-objcopy -j .text -j .data -O ihex hello-world.elf hello-world.hex

hello-world.elf: hello-world.o
	avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.o -o hello-world.elf

hello-world.o: hello-world.c
	avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL hello-world.c -o hello-world.o
```

Now if we run `make` again, we'll see all of our files get generated.  

This is a good improvement over our shell script, but what if we added a second file to our project?  
Would we need to add an object target for each `*.c` file in our project?  

Well... kind of, but we can do it much cleaner than you think.  
Make has a number of built in [automatic variables](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html).  
We can leverage these obscure symbols in our makefile to create _recipes_ for building _types_ of files.  
In other words, instead of explicitly saying 

> This is how to build this object file and this is how to build _that_ object file.

we'll create generic rules (or _recipes_) for transforming one type of file into another type of file.

The two automatic variables we'll use to accomplish this are `$@`, which captures the target name, and `$^` which captures the list of preresequite files.  
Let's replace the rule to create our object file with this one.

```makefile
%.o: %.c
	avr-gcc -c -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL $^ -o $@
```

Now, if we need to add a new file to our project, we can just add it to the list of preresequites for our `*.elf` file.  
For example: 

```makefile
hello-world.elf: hello-world.o goodbye.o
	avr-gcc -Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL $^ -o $@
```

And Make will automatically compile and link our new `*.c` files.

In addition to this, we can automatically detect all the source files as well as leverage [implicit variables](https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html) and user defined variables to DRY our `makefile`s out.

Creating `makefile`s is a fairly deep topic, and we've barely scratched the surface.  
I encourage you to [read the documentation](https://www.gnu.org/software/make/manual/html_node/) and learn more, but I mostly wanted to give you a brief introduction to the topic.  

For the remainder of this course, we'll use the avr-template makefiles I've already created that are available on GitHub.

https://github.com/rubberduck203/avr-template