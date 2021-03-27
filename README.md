# Embedded HW4: Kinetic Sculpture

This is the code repository for Creative Embedded Systems' kinetic sculpture project. When powered, this sculpture will animate whenever the button at <a href="http://165.227.76.232:3000/mhl2157">this link</a> is pressed.

Usage:
The code above is intended for use with a 5v DC step motor in conjunction with an ESP32 Wrover module and a step motor drive board. The code is currently set to connect the ESP32 to local wifi and to repeatly ping a link that returns a simple bool value. When the value is true, the loop action activates. Wifi credentials are accessed through credentials.h (not included in this repo). For personal usage, clone this repo, fill in the included .h template for your Wifi credentials, and include them in the code instead of "credentials.h".DO NOT COMMIT YOUR OWN WIFI TO GITHUB.

For further instructions regarding the materials used with this motor, visit, <a href="https://edblogs.columbia.edu/comsx3930-001-2021-1/?p=789&preview=true">the blog past here</a>.

Big thanks to <a href="https://maxs.world/">Max Bennett</a> for putting the API together and for providing <a href="https://github.com/mbennett12/kinetic-sculpture-webapi/blob/main/example_HTTP_get.ino">sample HTML GET</a> code for Arduino devices. 
