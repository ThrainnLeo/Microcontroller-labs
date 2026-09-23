#include "gd32vf103.h"
#include "drivers.h"
#include "lcd.h"

int main(void){
    int ms=0, s=0, key, pKey=-1, c=0, idle=0;
    int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};
    int dac=0, speed=-100;
    int adcr, tmpr;
    char digits[10][10]={"Zero ","One  ","Two  ","Three", "Four ", "Five ", "Six  ","Seven", "Eight", "Nine "};

    t5omsi();                               // Initialize timer5 1kHz
    colinit();                              // Initialize column toolbox
    l88init();                              // Initialize 8*8 led toolbox
    keyinit();                              // Initialize keyboard toolbox
    Lcd_SetType(LCD_INVERTED);              // or use LCD_INVERTED!
    Lcd_Init();
    LCD_Clear(BLACK);
    LCD_ShowStr(10, 10, "BATTERY TIME", WHITE, TRANSPARENT); // Vi kallar på BCD-koden (typ som printf), Vi skapar batterierna genom ascii kod
    int inputed = 0;
    while (1) {
        idle++;                             // Manage Async events
        LCD_WR_Queue();                    // Manage LCD com queue!

        if (t5expq()) {                     // Manage periodic tasks
            l88row(colset());               // ...8*8LED and Keyboard
            ms++;                           // ...One second heart beat
            if (ms==1000){
              ms=0;
              l88mem(0,s++);
              LCD_ShowStr(10, 30, digits[s%10], WHITE, OPAQUE);  
             
            }
            if ((key=keyscan())>=0) {       // ...Any key pressed?
              if (pKey==key) c++; else {c=0; pKey=key;}
              inputed = lookUpTbl[key]+(c<<4);

            }
             if (inputed == 0){                        // LCD_ShowChar --> visar vilken minnescell det ska vara
              LCD_ShowChar(10, 50, 130, 0, GREEN);     // 2 första siffrorna visar vart i displayen det ska vara
              LCD_ShowStr(30, 50, "100%          ", WHITE, OPAQUE);
            }                                          // 3 siffran --> vilken rad (index på listan), 4 siffran är vilket mode (transparant)
            else if (inputed == 1){
              LCD_ShowChar(10, 50, 129, 0, GREEN);
              LCD_ShowStr(30, 50, "70%            ", WHITE, OPAQUE);

            }
            else if (inputed == 2){
              LCD_ShowChar(10, 50, 128, 0, YELLOW);
              LCD_ShowStr(30, 50, "50%            ", WHITE, OPAQUE);

            }
            else if(inputed == 3){
              LCD_ShowChar(10, 50, 127, 0, RED);
              LCD_ShowStr(30, 50, "20%             ", WHITE, OPAQUE);

            }
            else if (inputed == 4) {
              LCD_ShowChar(10, 50, 126, 0, RED);
              LCD_ShowStr(30, 50, "0% ", WHITE, OPAQUE);
              LCD_ShowStr(50, 50, "CHARGE NOW!", WHITE, OPAQUE);

            }
            l88mem(2,idle>>8);              // ...Performance monitor
            l88mem(3,idle); idle=0;
        }
    }
}