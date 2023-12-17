# AC controller
AC controller which works on a MHI-AC-Ctrl module. It is using the MQTT messages to communicate with the MHI-AC_Ctrl module.

It is based on a Wireless Tag WT32-SC01 Plus display module with an integrated ESP32.
Layout is designed with Squareline Studio. Export to the UI directory and copy files to the src directory.
I used Visual Studio Code with platformIO to compile. 

I used a 3D printed case from https://www.printables.com/model/381026-wt32-sc01-plus-desk-case

Some pictures:

<img src="/images/image1.jpg" width=400 /> <img src="/images/image2.jpg" width=400 /><br>
Here you can control the AC:
- on and off
- change mode
- change fan speed
- change setpoint

You can click on:
- vanes icons to go to settings screen
- power symbol to go to the power usage chart
- current temperature in the middle to go to the current temperature chart
- settings icon to go to the settings page

It shows:
- status wifi connection
- defrost active or not (you don't see it now)
- fan speed IU
- vanes and vanesLR
- 3Dauto (you don't see it now)
- power usage in Watt (estimate)
- power usage in kWh
- outdoor temperature
- Troom temperature in the cirle in the middle
- power on/off, mode and fan
- setpoint

<img src="/images/image3.jpg" width=400 /><br>
Graph with current temperature from Troom for the last 10 minutes. For all graphs the data comes in from right to left.<br>
Graph with compressor speed for the last 10 minutes. 

<img src="/images/image4.jpg" width=400 /><br>
Graph with fan speed IU for the last 10 minutes.

<img src="/images/image5.jpg" width=400 />
Graph with power usage for the last 10 minutes.


<img src="/images/image6.jpg" width=400 /><br>
Settings to control:
- 3D auto
- Vane
- VaneLR
- Restart MHI-AC-Ctrl controller
- Brightness display
- Snooze display (after 2 min)
- Autocontrol is something private from me. So you have to remove that one.

Settings are stored on the MQTT server.



