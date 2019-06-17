// Require the serialport node module
var SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

var readline = require('readline');
var log = console.log;

var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

var recursiveAsyncReadLine = function () {
    rl.question('Msg to Ard: ', (output) => {
        // Base CASE => exit 
        if (output == 'exit'){ 
            return rl.close(); //closing RL and returning from function.
        }    
        
        // Writing to arduino
        port.write(output, (err) => {
            if(err){
                return console.log('ERROR: ', err.message);
            }
            log(`SENT: ${output}`);
        });

        recursiveAsyncReadLine(); //Calling this function again to ask new question
  });
}


const port = new SerialPort('/dev/ttyACM0', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));

// Read the port data
port.on("open", () => {
	console.log('serial port open');
});


parser.on('data', data =>{
  	console.log('got word from arduino:', data);
    recursiveAsyncReadLine(); //we have to actually start our recursion somehow
});



read_loop = function(){
	readline.question('Message to Arduino: ', (output) => {
		port.write(output, (err) => {
		    if (err) {
		        return console.log('Error on write: ', err.message);
		    }
	  		console.log(`SENT: ${output}!`)
		});
	  	readline.close()
	});
}
