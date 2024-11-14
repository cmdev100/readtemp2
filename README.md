# Readtemp version 2

Readtemp2 is the c++ version of Read temp (1) that was written in Python.
This is an exersise for me to learn c/c++ in a Linux environment with Visual Studio Code.

Readtemp2 reads the current temperature value from a temperature sensor connected to a Raspberry Pi. The temperature sensor is a 1-Wire DS18B20 and connects to GPIO pin 4.

## Function

There are four executables:
- **readTemp2**, The main program that stores a temperature value every hour (when the minute is 0). Will run as a service.
- **getMomentanValue** reads the current temperature value.
- **readTempValues** prints the desired count of stored values to the console. Default is 5.
- **storeCurrentValue** stores the current value and timestamp in the database.

The values are stored in a sqlite database along with the executables. The database file is called readtemp.db.
