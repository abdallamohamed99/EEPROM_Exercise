# EEPROM Exercise

The main goal of this program is to read the EEPROM first when the board is turned on and then depending on the value read from the EEPROM,
it will output a PWM signal to the LED to control its brightness. 
When the board is plugged into power for the first time the LED should be at 0% and then the next time it’s plugged to power the 
LED brightness should increase to 10% and so on until it reaches 100%. Once it reaches 100%, the LED should start over with 0% brightness.
