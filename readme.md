# lightmeter

#### Arduino project with lightmeter / luxmeter for old film cameras

###### [still in progress]

### requirements: 
#### hardware:
- arduino nano/uno (ATMega328 based)
- GY-302 (BH1750) lightsensor
- 128*64 lcd display, 6 pin SPI interface. [example](https://aliexpress.ru/item/32812310477.html) 
- 2 10k resistors
- 2 buttons
#### software:
- arduino IDE
- TM1637Display by Avishay Orpaz v1.2.0
- BH1750 https://github.com/claws/BH1750
- python 3.7+ (for config autogeneration)

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
