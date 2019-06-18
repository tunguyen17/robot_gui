# robot_gui

Install the necessary packages

$npm install

Starting the server | note that it only work if the arduino is on port ttyACM0

$npm start

# Arduino

The code for the arduiono is in "Arduino Code/commmunication/communication.ino"

This is simply a repeater. It repeat whatever the seral input was.

# Computer

Node js act as a server that interact with the arduino. 

The terminal will accept input and send the message to the arduino through the serial port. 

Note that: The message must be surrouneded with "<" and ">". For example <howdy, texas>

To start the server: 
- make sure that the arduino is on port ttyACM0. Need to fix this.
- run $npm start
