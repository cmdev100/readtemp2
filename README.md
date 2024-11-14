# Read temp v2

Read temp 2 is the c++ version of Read temp (1) that was written in Python.
This is an exersise for me to learn c/c++ in a Linux environment with Visual Studio Code.

## Function

There are four executables:
<ul>
  <li>***readTemp2*** that stores a temperature value every hour (when the minute is 0). Will run as a service.</li>
  <li>***getMomentanValue*** reads the current temperature value.</li>
  <li>***readTempValues*** prints the desired count of stored values to the console. Default is 5.</li>
  <li>***storeCurrentValue*** stores the current value and timestamp in the database.</li>  
</ul>

The values are stored in a sqlite database along with the executables. The database file is called readtemp.db.
