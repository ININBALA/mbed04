#include "mbed.h"

Serial pc( USBTX, USBRX );
AnalogIn Ain(A0);
AnalogOut Aout(DAC0_OUT);
DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
float period = 0;
int flag = 0;
int sample = 0;
int i = 0;
float j = 0;
float k;
float data;
int freq;
float ADCdata[500];

int main(){

  for(i = 0; i < 430; i++){
    data = Ain;
    pc.printf("%1.3f\r\n", data);
    wait(0.002325581395);
  }
  while(1){
    if( Switch == 0){
      greenLED = 1;
      redLED = 0;
        
      display = table[freq/100];
      wait(0.5);        

      display = table[freq/10%10];
      wait(0.5);

      if( i%10== 0)
          display = 0xBF;
      else
          display = table[freq%10];
      wait(0.5);
    }
    else{
      greenLED = 0;
      redLED = 1;
      display = 00000000;
      if(freq != 0){
        for(j = 0; j < 2; j += 0.05){
          Aout = 0.5 + 0.5 * sin(j*3.14159);
          wait(1./freq/53);
        }
      }
      else{
        for(i = 0; i < 500; i++){
          ADCdata[i] = Ain;
          wait(0.002);
        }
        for(i = 0; i < 500; i++){
          if(ADCdata[i-1] < ADCdata[i] && ADCdata[i] > ADCdata[i+1])
            freq++;
        }
      } 
    }
  }
}