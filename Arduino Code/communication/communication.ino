
// Declaration for serial communication
const byte numChars = 32; // max number of character
char receivedChars[numChars]; // holder for incomming data
char signalType[numChars] = {0};
int signalVal = 0;
boolean newData = false; // boolean to keep track if new data has been read

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  // Fetch command from serial
  recvWithStartEndMarkers();

  showNewData();
  response();
//  Serial.println("Howdy, Texas!");
}

void response() {
  
  // NOTE: only response if new data is true

  if(newData == true) {
    // NEW DATA RECIEVED
    // -----------------

    // Printing recieved data
    Serial.println(receivedChars);

    // Start parsing data into controlType and controlVal
    char * strtokIndx; // this is used by strtok() as an index
  
    strtokIndx = strtok(receivedChars,",");      // get the first part - the string
    strcpy(signalType, strtokIndx); // copy it to messageFromPC
  
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    signalVal = atoi(strtokIndx);     // convert this part to an integer

    // printing parsed data
//    Serial.print(signalType);
//    Serial.print(',');
//    Serial.println(signalVal);

      
    // -----------------
    // End of cycle & start new
    newData = false;
    }  
    //showNewData();

    //----------------------------
  }

//| ---------------------------  |//
//| SENDING AND RECIEVING SIGNAL |
//| ---------------------------  |//
// source: https://forum.arduino.cc/index.php?topic=288234.0

void recvWithStartEndMarkers() {
  /*
   * Function to read incomming signal
   * 
   * NOTE: incomming signal must begin with '<' and end with '>'
   */

  static boolean recvInProgress = false;
  static byte ndx = 0; // Initialize starting position

  // declare start and end marker
  char startMarker = '<';
  char endMarker = '>';
  
  char rc; // recieving character

   
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1; // if the buffer is full replace the last character
          }
        }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
        }
      }
    else if (rc == startMarker) {
      // only start recieving character when the starting character is recieved
      recvInProgress = true;
      }
    }
}

void showNewData() {
  /*
   * Print out data
   */
  if (newData == true) {
    Serial.println(receivedChars);
    newData = false;
    }
}






  
//| --- |//
//| END |
//| --- |//
