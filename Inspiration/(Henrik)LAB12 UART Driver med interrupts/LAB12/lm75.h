/****************************************
* "LM75.h":                             *
* Header file for LM75 driver.          *
* LM75 is an I2C temperature sensor.    *
* Temperature is returned in HALFs of   *
* centigrades.                          *
*                                       *
* Henning Hargaard, 13/11 2015          *
*****************************************/
void LM75_init();
int LM75_temperature(unsigned char SensorAddress);
/****************************************/