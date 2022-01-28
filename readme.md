# ESP32

Provides webserver for Hexastorm using MicroPython.
Webserver is based upon [MicroWebSrv2](https://github.com/jczic/MicroWebSrv2).

# Install
Ubuntu is required. Ubuntu WSL cannot communicate with com port.
This makes development on Windows more difficult.
You need to compile MicroPython with the [MicroWebSrv2](https://github.com/jczic/MicroWebSrv2).  
Clone micropython, build the cross-compiler and go to
the ports/esp32 directory. Follow the instruction outlined [here](https://docs.micropython.org/en/latest/develop/gettingstarted.html).
In the readme located in ports/esp32, you will find the instruction on how to download and use esp-idf.
On ubuntu you might need,
```sudo apt-get install python-is-python3```
Build the generic version of MicroPython.
Place MicroWebSrv2, only the MicroWebSrv2 subfolder, into the modules directory. This is known as a frozen [module](https://learn.adafruit.com/micropython-basics-loading-modules/frozen-modules).
Recompile, check the module is cross compiled, erase the flash
and flash the new binary to the memory.

A usefull tool to interact with the ESP32 is [rshell](https://github.com/dhylands/rshell).
You can connect with the esp32 via
```connect serial /dev/ttyUSB0``` or
```connect serial com6``` on Windows.
The flash memory is available as /flash or /pyboard.
```repl``` gives you an interactive developer environment with
the board.
Esptool can also be used to flash and erase the ESP32. 
