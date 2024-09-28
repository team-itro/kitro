## greymatter v0

brains of kitro v011

## stm32cubeide guide

it should just work when you open the folder as a project in stm32cubeide

1. `Core` folder contains the stm32cubemx generated hal configuration files
2. `Library` folder contains the organized utility and helper functions specific to each modules and abilities of kitro
3. `Program` folder contains the main entry point and loop which are then called in the main.c to override. we also have the algorithm files here.

### painpoints

- you might accidently set resource configuration to a certain file which then you can clear by right clicking on the certain file and resource configuration context menu item and uncheking all and applying.

- make sure you have installed the specific microcontroller toolchain, stm32f4 series in our case, before trying to build

- make sure to include new include directories (if added) to both c and cpp compiler options in project properties

- stm32 is a 3.3v operated microcontroller, don't do dumb things trying to connect 5v pushbuttons

### references

https://github.com/sanjith1999/SINDiB-MicroMouse/tree/master/firmware
