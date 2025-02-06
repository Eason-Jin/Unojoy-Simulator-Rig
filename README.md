# Unojoy-Simulator-Rig
This is a simple Unojoy controller I configured to play Euro Truck Simulator 2.
## Phase 1
A simple mockup of the controller with some off-the-shelf components, including push buttons, potentiometers, rotary encoders and switches. \
\
A picture of the mockup os shown below:
![Mockup](Assets/dashboard.jpg)

The configration is as follows:
* 1 [Arduino Uno](https://surplustronics.co.nz/products/7014-arduino-uno-r3-clone-with-usb-cable).
* 1 [rotary encoder](https://surplustronics.co.nz/products/10776-rotary-encoder-module) for the steering wheel.
* 3 [potentiometers](https://surplustronics.co.nz/products/1686-10k-ohm-linear-potentiometer-) for the throttle, brake and clutch. Another one will be added later for the camera.
* 2 [toggle switches](https://surplustronics.co.nz/products/4314-switch-toggle-on-on-spdt-3-pins-panel-mount) as engine brake switch and high-low gear selector.
* 7 [tactile push buttons](https://surplustronics.co.nz/products/2159-switch-tact-push-button-momentary) for 6 forward gears and 1 reverse gear.

The wiring diagram is shown below:
![Wiring diagram](Assets/image.png)

Videos of the controller in action are under the `Assets` folder.

Shifting through a 12 speed with only hand controls is hard😅. So in phase 2 I will visit the near by wreckers to salvage some parts.

## Phase 2
I will be constructing this simulator using 3D printed parts and off-the-shelf hardware. All CAD files are found under the `CAD` folder. CAD models are made with Autodesk Inventor.
### Steering Assembly
The steering wheel will be sandwiched between the grey and purple parts. The main steering shaft is a 32mm diameter PVC pipe.\
\
Front view:
![Steering front](Assets/steering%20CAD%20front.png)

Rear view:
![Steering rear](Assets/steering%20CAD%20rear.png)

A rubber band will be attached to the orange part and goes to the support structure. This will provide auto-centering force.\
\
The support structure and the two red posts will be screwed to a wooden base plate with M8 screws.