
#include <iostream>
#include <wiringPi.h>
#include <math.h>

using namespace std;

int const dpin = 21;
int c, i = 0, byte[4];

int main () {

wiringPiSetupGpio();

pinMode(dpin, OUTPUT);
digitalWrite(dpin, 0);
delay(18);
digitalWrite(dpin, 1);
pinMode(dpin, INPUT);

bool *data = new bool[41];

while (i < 41) {
	if (digitalRead(dpin) == 1) {
		c = 0;
		while(digitalRead(dpin) == 1) {
			delayMicroseconds(1);
			c = c+1;
			if (c > 75) {
				break;
			}
		}
		if ( c > 30) {
			data[i] = 1;
		}
		else {
			data[i] = 0;
		}
		i = i + 1;
	}
}

for (i = 0; i < 5; i++) {

	int j = 1 + 8*i;
	c = 0;
	for (int k = 0; k < 8; k++) {
		if (data[j+k] == 1) {
			byte[i] = byte[i] + pow(2, 7-k);
		}
	}
}
if ( (byte[0]+byte[2])%255 == byte[4] % 255 ) {
	cout << "Temperatur: " << byte[2] << "°C  ";
	cout << "Luftfeuchtigkeit: " << byte[0] << "%" << endl;
}
else {
	cout << "recieved corrupt data" << endl;
}
delete[] data;


return 0;
}
