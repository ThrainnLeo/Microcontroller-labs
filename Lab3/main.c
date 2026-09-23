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
    //T1powerUpInitPWM(0x4);                  // Timer #1, Ch #2 PWM
    //T1powerUpInitPWM(0x8);                  // Timer #1, Ch #2 & 3 PWM

    int sin[10] = {1000, 900, 800, 700, 600, 500, 400, 300, 200, 100};//en tabell med förprogrammerade värden för att du ska kunna ha sample and hold (digital till analog)
    int i = 0; // Skapade en sinuskurva som var försjuten till 1000 och tog 10 punkter från den posetiva delen av perioden 
    int inputed = 0;
    while (1) {
        // idle++;                             // Manage Async events
        l88row(colset());                     
        if (t5expq()) {                     // Manage periodic tasks
        
            DAC0set(sin[i]);               // förprogrammerade värden skickar värden till dac_data_set
            i++;
            if (i > 9) i = 0;           // Säger att elementet (i) är 0-9 i arrayen
        
        }
        if ((key=keyscan())>=0) {       // ...Any key pressed?
              if (pKey==key) c++; else {c=0; pKey=key;}
              inputed = lookUpTbl[key]+(c<<4); // kolla om varför den måste försjutas med fyra bitar 
            

              switch (inputed){ // Detta är alla toner för varje nummer på keypaden

                case 0: ton(440); break;// 0
                case 1: ton (262); break;// 1

                case 2: ton(277); break;// 2
                case 3: ton(294); break;// 3

                case 4: ton(311); break;// 4
                case 5: ton(330); break;// 5

                case 6: ton(349); break;// 6
                case 7: ton(370);break;// 7

                case 8: ton(392); break;// 8
                case 9: ton(415); break;// 9

                case 10: ton(466); break;// A 
                case 11: ton(494); break;// B

                case 12: ton(523); break;// C
                case 13: ton(587);break;// D

                case 14: ton(659);break;// * 
                case 15: ton(698);break;// #
              }
        }
    }
}