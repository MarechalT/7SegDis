#include <wiringPi.h>
#include <iostream>
#include "translator7SD.h"
// Using a 74HC595

#define SER 0   // Serial Data Input
#define RCLK 1  // Register Clock
#define SRCLK 3	// Shift Register Clock

#define D0 4	//Pin to drive the first 7SD
#define D1 5	//Pin to drive the second 7SD
#define D2 6	//Pin to drive the third 7SD
#define D3 7	//Pin to drive the fourth 7SD

using namespace std;
extern const int signs[];
unsigned char SegCode[19]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x38,0x3e,0x80};

void init(){
	pinMode(SER,OUTPUT);
	pinMode(RCLK,OUTPUT);
	pinMode(SRCLK,OUTPUT);
	pinMode(D0,OUTPUT);
	pinMode(D1,OUTPUT);
	pinMode(D2,OUTPUT);
	pinMode(D3,OUTPUT);
	digitalWrite(SER, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);

	digitalWrite(D0,1);
        digitalWrite(D1,0);
        digitalWrite(D2,0);
        digitalWrite(D3,0);
}

void hc595_shift(unsigned char dat){

        for(int i=0;i<8;i++){
                digitalWrite(SER, 0x80 & (dat << i));
                digitalWrite(SRCLK, 1);
                delayMicroseconds(100);
                digitalWrite(SRCLK, 0);
        }

        digitalWrite(RCLK, 1);
        delayMicroseconds(50);
        digitalWrite(RCLK,0);
}


int main(){

	if(wiringPiSetup() == -1){
		cout << "Setup wiringPi Failed" << endl;
		return 1;
		}
	init();
	while(1){
		for(int i=0;i<94;i++){
			hc595_shift(signs[i]);
			delay(500);
		}
	}

	return 0;
}


