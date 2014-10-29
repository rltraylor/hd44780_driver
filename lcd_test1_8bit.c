// lcd_test1.c
//Roger Traylor
//test for 8 bit lcd interface - temporary

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "hd44780.h"

char lcd_test[17]  = {"***-LCD_Test-***"};

//uint8_t quarter_note_char[8] = {
//    0x04, //           |  #  |
//    0x06, //           |  ## |
//    0x05, //Generates  |  # #|
//    0x05, //-------->  |  # #|
//    0x04, //           |  #  |
//    0x1C, //           |###  |
//    0x1C, //           |###  |
//    0x00, //           |     |
//    };

//uint8_t bar0 [8] = {0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00};
//uint8_t bar1 [8] = {0x00, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00};
//uint8_t bar2 [8] = {0x00, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x00};
//uint8_t bar3 [8] = {0x00, 0x1F, 0x1C, 0x1C, 0x1C, 0x1C, 0x1F, 0x00};
//uint8_t bar4 [8] = {0x00, 0x1F, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x00};
//uint8_t bar5 [8] = {0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00};

uint8_t no_bar    [8] = {0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00};
uint8_t one_bar   [8] = {0x10, 0x10, 0x10, 0x15, 0x10, 0x10, 0x10, 0x00};
uint8_t two_bar   [8] = {0x14, 0x14, 0x14, 0x15, 0x14, 0x14, 0x14, 0x00};
uint8_t three_bar [8] = {0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x00};

/* This must be run before attempting to write to the LCD in SPI mode.*/
//void spi_init(void){ 
// DDRB=0x07;  //Turn on SS, MOSI, SCLK 
// //Master mode, Clock=clk/2, Cycle half phase, Low polarity, MSB first  
// SPCR=0x50;
// SPSR=0x01;
// }


/********** main() follows *********/  
int main () {

int8_t i;

int32_t j;

//initalize the SPI port and then the LCD
//  spi_init();

  lcd_init(); 
  clear_display();

//put quarter note character into CGRAM location zero
//set_custom_character(quarter_note_char, 0x01);
//set_custom_character(bar0, 0x01);
//set_custom_character(bar1, 0x02);
//set_custom_character(bar2, 0x03);
//set_custom_character(bar3, 0x04);
//set_custom_character(bar4, 0x05);

set_custom_character(no_bar, 0x01);
set_custom_character(one_bar, 0x02);
set_custom_character(two_bar, 0x03);
set_custom_character(three_bar, 0x04);
/********** LCD test **********/  
/*
The string "***-LCD_Test-***" is sent to both LCD lines and held for 1sec.
Then LCD is then cleared for 0.6 sec and the pattern is repeated.
*/ 

while(1){ 

  for(i=0; i<=1; i++){     //blink 2 times 
    string2lcd(lcd_test);  //send string to LCD
    home_line2();          //move cursor to line2
    string2lcd(lcd_test);  //send string again
    _delay_ms(200);
    _delay_ms(200);
    clear_display();
    _delay_ms(200);
    _delay_ms(200);
    cursor_home();         //put cursor back to home position
  }//for

  string2lcd(lcd_test);  //send string to LCD
  home_line2();          //move cursor to line2
  string2lcd(lcd_test);  //send string again
  cursor_home();         //put cursor back to home position
  
  for(i=0; i<=15; i++){     //shift it all right 16 times
    shift_right();
    _delay_ms(50);
  }
  _delay_ms(200);
  _delay_ms(200);
  _delay_ms(200);
  
  for(i=0; i<=15; i++){     //shift it all left 16 times
    shift_left();
    _delay_ms(50);
  }

  cursor_home();         //put cursor back to home position
  fill_spaces();         //fill line one with spaces
  cursor_home();         //put cursor back to home position


  for(i=0; i<=7; i++){   //count right and up
  uint2lcd(i); 
  _delay_ms(300);
  }
  
  for(i=7; i>=0; i--){   //continue counting right but down
  uint2lcd(i); 
  _delay_ms(300);
  }

  clear_display();
  _delay_ms(200);
  _delay_ms(200);

  for(i=-8; i<=8; i++){
    set_cursor(1,7);     //move cursor to middle to top row
    int2lcd(i);          //count backwards
    _delay_ms(300);
    set_cursor(1,7);     //move cursor to middle to top row
    char2lcd(' ');       //erase characters
    char2lcd(' ');
    char2lcd(' ');
  }
  _delay_ms(200);
  _delay_ms(200);

/*
  clear_display();
  cursor_on();
  _delay_ms(500);
  set_cursor(1,0);   _delay_ms(500); set_cursor(2,0); _delay_ms(500);
  set_cursor(1,1);   _delay_ms(500); set_cursor(2,1); _delay_ms(500);
  set_cursor(1,2);   _delay_ms(500); set_cursor(2,2); _delay_ms(500);
  set_cursor(1,3);   _delay_ms(500); set_cursor(2,3); _delay_ms(500);
  set_cursor(1,4);   _delay_ms(500); set_cursor(2,4); _delay_ms(500);
  set_cursor(1,5);   _delay_ms(500); set_cursor(2,5); _delay_ms(500);
  set_cursor(1,6);   _delay_ms(500); set_cursor(2,6); _delay_ms(500);
  set_cursor(1,7);   _delay_ms(500); set_cursor(2,7); _delay_ms(500);
  set_cursor(1,8);   _delay_ms(500); set_cursor(2,8); _delay_ms(500);
  set_cursor(1,9);   _delay_ms(500);
  set_cursor(1,10);   _delay_ms(500);
  set_cursor(1,11);   _delay_ms(500);
  set_cursor(1,12);   _delay_ms(500);
  set_cursor(1,13);   _delay_ms(500);
  set_cursor(1,14);   _delay_ms(500);
  set_cursor(1,15);   _delay_ms(500);
  cursor_off();
  _delay_ms(500);

*/

clear_display();
cursor_home();

  for(j=12345670; j<=12345678; j++){   //count up with big int 32's
  lcd_int32(j,12,0,0,0); 
  _delay_ms(500);
  cursor_home();
  }

  _delay_ms(1500);
  
  clear_display();
  cursor_home();
  for(j=14550; j>=14540; j--){   //count up with big int 32's
  lcd_int16(j,10,0,0); 
  _delay_ms(500);
  cursor_home();
  }

/*
string2lcd("custom: \1");
  _delay_ms(500);
string2lcd("\1");
  _delay_ms(500);
string2lcd("\1");
  _delay_ms(500);
string2lcd("\1");
  _delay_ms(500);
string2lcd("\1");
  _delay_ms(500);
string2lcd("\1");
  _delay_ms(500);
string2lcd("\1");
  _delay_ms(500);
string2lcd("\1");
  _delay_ms(500);
  _delay_ms(500);


*/
/*
clear_display();

for(i=0; i<=15; i++){ string2lcd("\1");} //fill with blanks
cursor_home();
_delay_ms(100);

for(i=0; i<=4; i++){
set_cursor(1,i);
string2lcd("\2");
  _delay_ms(50);
set_cursor(1,i);
string2lcd("\3");
  _delay_ms(50);
set_cursor(1,i);
string2lcd("\4");
  _delay_ms(50);
}

*/

}//while
 
}//main
