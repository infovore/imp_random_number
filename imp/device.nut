// set up arduino on hardware UART
arduino <- hardware.uart57;
arduino.configure(9600, 8, PARITY_NONE, 1, NO_CTSRTS);

function getRandomNumber() {
  server.log("*** Asking for a random number");
  agent.send("getRand", 1);

  // schedule imp to wakeup in 3 seconds and do it again. 
  imp.wakeup(3, getRandomNumber);
}
 
// start that looping
getRandomNumber();

// handle a packet of JSON when it comes in
function handleRandomNumber(data) {
  // send the random number as a uart message to our Arduino
  server.log("*** Sending arduino the random number " + data.number);
  local string = "N " + data.number + "\r";
  arduino.write(string);
}

// handle messages from the server
agent.on("rand", handleRandomNumber);