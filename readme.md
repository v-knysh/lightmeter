# lightmeter

#### Arduino project with lightmeter / luxmeter for old film cameras

###### [still in progress]

### requirements: 
- python 3.7+
- arduino IDE
- TM1637Display by Avishay Orpaz v1.2.0
- BH1750
- Servo (?)
- 2 10k resistors
- 2 buttons

### build
updating shutter speed and aperture values is a tricky task so
its is easier to do that on compile stage. here is python script
that builds files with constants based on json file located in confids folder. 

##### stages:
1. run `python3 build_constants.py fed5.json`
2. open Arduino IDE
3. compile and upload

### Notes:

calibratedEv should be filled by experimental data. better results would be if light sensor will be in its final position.
I hope linear fit would be ok, so wolfram alpha "linear fit" would be enough

buttons are connected with Pull DOWN Resistor scheme. others dont work somehow. 




