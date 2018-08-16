#include <wiringPi.h>
#include <iostream>

// Using a 74HC595

#define SER 0   // Serial Data Input
#define RCLK 1  // Register Clock
#define SRCLK 3	// Shift Register Clock

#define D0 4	//Pin to drive the first 7SD
#define D1 5	//Pin to drive the second 7SD
#define D2 6	//Pin to drive the third 7SD
#define D3 7	//Pin to drive the fourth 7SD

using namespace std;

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

	digitalWrite(D0,0);
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

void hc595_select_display(unsigned int disp){
	switch(disp){
	case 0:
			digitalWrite(D0,1);
			digitalWrite(D1,0);
                        digitalWrite(D2,0);
                        digitalWrite(D3,0);
		break;

 	case 1:
                        digitalWrite(D0,0);
                        digitalWrite(D1,1);
                        digitalWrite(D2,0);
                        digitalWrite(D3,0);
                break;

	case 2:
                        digitalWrite(D0,0);
                        digitalWrite(D1,0);
                        digitalWrite(D2,1);
                        digitalWrite(D3,0);
                break;
  	case 3:
                        digitalWrite(D0,0);
                        digitalWrite(D1,0);
                        digitalWrite(D2,0);
                        digitalWrite(D3,1);
                break;
	default:
		cout << "error selecting the display" << endl;
	}
}

void iLoveFood(){
	while(1){
	// I
	hc595_shift(SegCode[1]);
        hc595_select_display(0);
	delay(500);

	//LOve
        for(int i=0;i<300;i++){
	hc595_shift(SegCode[16]);
	hc595_select_display(0);
	delayMicroseconds(50);
	hc595_shift(SegCode[0]);
	hc595_select_display(1);
        delayMicroseconds(50);
	hc595_shift(SegCode[17]);
	hc595_select_display(2);
	delayMicroseconds(50);
        hc595_shift(SegCode[14]);
	hc595_select_display(3);
	delayMicroseconds(50);
		}

	//fOOd
	for(int j=0;j<300;j++){
        hc595_shift(SegCode[15]);
	hc595_select_display(0);
        delayMicroseconds(2);
        hc595_shift(SegCode[0]);
	hc595_select_display(1);
        delayMicroseconds(2);
        hc595_shift(SegCode[0]);
	hc595_select_display(2);
        delayMicroseconds(2);
        hc595_shift(SegCode[13]);
	hc595_select_display(3);
        delayMicroseconds(2);
		}
	}
}

int main(){

	if(wiringPiSetup() == -1){
		cout << "Setup wiringPi Failed" << endl;
		return 1;
		}
	init();
	while(1){
/*		for(int i=0;i<19;i++){
			hc595_shift(SegCode[i]);
			hc595_select_display((i%4));
			delay(500);
		}
*/
	iLoveFood();
	}

	return 0;
}


