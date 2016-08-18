#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// make some custom characters:
byte numbers[11][8] = {
  {
    0b00000,
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b01110,
    0b00000,
    0b00000,
  },
  {
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000,
  },
  {
    0b00010,
    0b01010,
    0b01010,
    0b01010,
    0b01010,
    0b01010,
    0b00010,
    0b00000,
  },
  {
    0b00001,
    0b10101,
    0b10101,
    0b10101,
    0b10101,
    0b10101,
    0b00001,
    0b00000,
  },
  {
    0b11111,
    0b10101,
    0b11101,
    0b10001,
    0b11101,
    0b10011,
    0b11111,
    0b00000,
  },
  {
    0b00001,
    0b10111,
    0b10101,
    0b11101,
    0b10111,
    0b10101,
    0b00101,
    0b00000,
  },
  {
    0b01000,
    0b01001,
    0b01010,
    0b11000,
    0b01010,
    0b01001,
    0b01000,
    0b00000,
  },
  {
    0b00010,
    0b10001,
    0b01001,
    0b01001,
    0b11111,
    0b00100,
    0b00100,
    0b00000,
  },
  {
    0b00001,
    0b00110,
    0b11000,
    0b00000,
    0b11000,
    0b00110,
    0b00001,
    0b00000,
  },
  {
    0b00011,
    0b00001,
    0b01111,
    0b01000,
    0b11100,
    0b01010,
    0b01001,
    0b00000,
  },
  {
    0b00100,
    0b00100,
    0b00100,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00000,
  }
};

byte kanji[4][8] = {
  {
    0b01000,
    0b11111,
    0b01010,
    0b11111,
    0b10101,
    0b11111,
    0b00000,
    0b00000,
  },
  {
    0b01000,
    0b10110,
    0b00101,
    0b00110,
    0b10101,
    0b01000,
    0b00000,
    0b00000,
  },
  {
    0b00000,
    0b11111,
    0b10101,
    0b10100,
    0b11110,
    0b00001,
    0b00000,
    0b00000,
  },
  {
    0b00000,
    0b11111,
    0b10101,
    0b10101,
    0b10101,
    0b11111,
    0b00000,
    0b00000,
  }
};

byte blank[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

int hour = 23;
int min  = 59;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);

  lcd.createChar(0, blank);
  lcd.createChar(1, blank);
  lcd.createChar(2, blank);
  lcd.createChar(3, blank);
  lcd.createChar(4, blank);
  lcd.createChar(5, blank);
  lcd.createChar(6, blank);
  lcd.createChar(7, blank);

  //  lcd.createChar(3, kanji[0]);
  //  lcd.createChar(7, kanji[1]));

  lcd.setCursor(0, 0);

  lcd.write((unsigned char)0);
  lcd.write((unsigned char)1);
  lcd.write((unsigned char)2);
  lcd.write((unsigned char)3);
  lcd.write((unsigned char)4);
  lcd.write((unsigned char)5);
  lcd.write((unsigned char)6);
  lcd.write((unsigned char)7);
  
  delay(1000);
}

void loop() {
  if (++min >= 60) {
    min = 0;
    if (++hour >= 24) {
      hour = 0;
    }
  }
  
//  hour = 23;
//  min  = 59;

  int hour_ten = hour / 10;
  int hour_one = hour % 10;

  int min_ten  = min  / 10;
  int min_one  = min  % 10;

  Serial.print(hour_ten);
  Serial.print(' ');
  Serial.print(hour_one);
  Serial.print(' ');
  Serial.print(min_ten);
  Serial.print(' ');
  Serial.print(min_one);
  Serial.println();

  if (hour_ten >= 2)
    lcd.createChar(0, numbers[hour_ten]);
  else
    lcd.createChar(0, blank);
    
  if (hour_ten >= 1)
    lcd.createChar(1, numbers[10]);
  else
    lcd.createChar(1, blank);
  
  if (hour_one == 0 && hour_ten > 0)  
    lcd.createChar(2, blank);
  else
    lcd.createChar(2, numbers[hour_one]);
     
  lcd.createChar(3, kanji[0]);
    
  
  if (min_ten >= 2)
    lcd.createChar(4, numbers[min_ten]);
  else
    lcd.createChar(4, blank);
    
  if (min_ten >= 1)
    lcd.createChar(5, numbers[10]);
  else
    lcd.createChar(5, blank);
    
  if (min_one == 0 && min_ten > 0)  
    lcd.createChar(6, blank);
  else
    lcd.createChar(6, numbers[min_one]);
    
  lcd.createChar(7, kanji[1]);

  delay(1000);

}
