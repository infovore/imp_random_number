// handle inbound message from the device
device.on("getRand", function(d) {
   server.log("### I've been asked for a random number");
   
   // get a number from http
   local url = "http://tomarmitage.com/tmp/rand.php";
   local request = http.get(url);
   local response = request.sendsync();
   local data = http.jsondecode(response.body);
   
   server.log("### Sending data to the imp: " + data);
   device.send("rand", data);
});