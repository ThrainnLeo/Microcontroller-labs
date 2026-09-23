#include "gd32vf103.h"
#include "drivers.h"
#include "dac.h"
#include "pwm.h"

int main(void){
    int ms=0, s=0, key, pKey=-1, c=0, idle=0;
    int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};
    int dac=0, speed=-100;

    t5omsi();                               // Initialize timer5 1kHz
    colinit();                              // Initialize column toolbox
    l88init();                              // Initialize 8*8 led toolbox
    keyinit();                              // Initialize keyboard toolbox
    //DAC0powerUpInit();                      // Initialize DAC0/PA4 toolbox
    //T1powerUpInitPWM(0x4);                  // Timer #1, Ch #2 PWM
    T1powerUpInitPWM(0x1);                  // Timer #1, Ch #2 & 3 PWM

    int thirdValue = 0;
    int secondValue = 0;
    int firstValue = 0;
    
    
    while (1) {
        idle++;                             // Manage Async events
        int inputed = 0;
        
 
        if (t5expq()) {                     // Manage periodic tasks
            l88row(colset());               // ...8*8LED and Keyboard
            ms++;                           // ...One second heart beat
            if (ms==1000){
              ms=0;
              
              speed+=10;
              if (speed>=100) speed=-100;
            }
            if ((key=keyscan())>=0) {       // ...Any key pressed?
              if (pKey==key) c++; else {c=0; pKey=key;}
              inputed = lookUpTbl[key]+(c<<4);
             

              if (inputed == 14){

                firstValue = secondValue;
                secondValue = thirdValue;
                thirdValue = 0;
              }
              else if (inputed == 15){
                thirdValue = 0;
                secondValue = 0;
                firstValue = 0;
              }
              else if(inputed == 13){
                
                    int LampPower = firstValue;
                    LampPower += 10*secondValue;
                    LampPower += 100* thirdValue;
                    if (LampPower > 100) LampPower = 100;
                    T1setPWMch2(LampPower *160);
                 
                  thirdValue = 0;
                  secondValue = 0;
                  firstValue = 0;
                  inputed = 0;

              }
              else {
                thirdValue = secondValue;
                secondValue = firstValue;
                firstValue = inputed;

              }
            }
        }
    }
}

                  //l88mem(0,s++);            //s = counter
              //T1setPWMmotorB(speed+=10);          // PWM T1/C23 Unit test
              //T1setPWMmotorB(4);
              //T1setPWMch2(15000);
                          //l88mem(2,idle>>8);              // ...Performance monitor
            //l88mem(3,idle); idle=0;
            //DAC0set(dac++);                 // DAC0 Unit test
            //T1setPWMch2(15000);               // PWM T1/C2 Unit test
    //hämta in de tryckta knappar och spara
    //använd T1SetPWMmoter


//DAC0powerUpInit
//T1powerUpInitPWM
//T1setPWMmotorB
//T1setPWMch2
//DAC0set
//lookUpTbl