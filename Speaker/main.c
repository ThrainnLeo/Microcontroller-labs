#include "gd32vf103.h" //jag måste lösa nån form av timer i koden till projekt kursen 
#include "drivers.h"
#include "dac.h"
#include "pwm.h"        // kallar på alla bibliotek 



int main(void){ 
    int ms=0, s=0, key, pKey=-1, c=0, idle=0;
    int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};
    int dac=0, speed=-100;

    t5omsi();                               // Initialize timer5 1kHz
    colinit();                              // Initialize column toolbox
    l88init();                              // Initialize 8*8 led toolbox
    keyinit();                              // Initialize keyboard toolbox
    DAC0powerUpInit();                      // Initialize DAC0/PA4 toolbox
    // T1powerUpInitPWM(0x4);                  // Timer #1, Ch #2 PWM
    // T1powerUpInitPWM(0x8);                  // Timer #1, Ch #2 & 3 PWM

    int sin[10] = {1000, 900, 800, 700, 600, 500, 400, 300, 200, 100};//en tabell med förprogrammerade värden för att du ska kunna ha sample and hold (digital till analog)
    int i = 0; // Skapade en sinuskurva som var försjuten till 1000 och tog 10 punkter från den positiva delen av perioden 
    int inputed = 0;
  
    while (1) {
        idle++;                             // Manage Async events
        l88row(colset());
        if (t5expq()) {                     // Manage periodic tasks
        
            DAC0set(sin[i]);               // förprogrammerade värden skickar värden till dac_data_set
            i++;
            if (i > 9) i = 0;           // Säger att elementet (i) är 0-9 i arrayen

            ms++;
            if(ms<=1000){
                tone(450);
            } else {
                break;
            }
        
        }
        // if ((key=keyscan())>=0) {       // ...Any key pressed?
        //       if (pKey==key) c++; else {c=0; pKey=key;}
        //       inputed = lookUpTbl[key]+(c<<4); // kolla om varför den måste försjutas med fyra bitar

        // }
    }
}