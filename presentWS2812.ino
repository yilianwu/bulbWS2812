#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(119, PIN, NEO_GRB + NEO_KHZ800);
int value;
void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    value = Serial.read();
    Serial.println(value);
  }
  //  colorWipe(strip.Color(0,255,0),100);
  //rainbow(10);
  //rainbowCycle(0.1);
  //theaterChase(strip.Color(0, 0, 127), 1000);
  //theaterChaseRainbow(1000);
      PinLin1(strip.Color(127, 127, 127), 10);  //color,speed
//      TZP1(1000); //speed
//      TZP2(2,20); //lednum,speed

//    TZP3(1000);
//    TZP4(strip.Color(127, 127, 127), 1000);
//    TZP5(10);
//   MOM1(15,20);
//  MOM2(1000);
  //mytest(strip.Color(0, 0, 127), 1000);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, rainbowWheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t rainbowWheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 0.01, 0, WheelPos * 0.01);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 0.01, 255 - WheelPos * 0.01);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 0.01, 255 - WheelPos * 0.01, 0);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, cycleWheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t cycleWheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 0.7, 0, WheelPos * 0.7);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 0.7, 255 - WheelPos * 0.7);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 0.7, 255 - WheelPos * 0.7, 0);
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, chaseWheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

uint32_t chaseWheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
//------------------PinLin-------------------//
void PinLin1 (uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) {
    uint16_t onLed [5];
    for (int i = 0; i < 5; i++) {
      onLed[i] = random(0, 120);
    }
    for (int i = 0; i < 5; i++) {
      strip.setPixelColor(onLed[i], c);
    }
    strip.show();
    delay(wait*0.01);
    for (int i = 0; i < 5; i++) {
      strip.setPixelColor(onLed[i], 0);
    }
  }
}
//--------------------TZP--------------------//
void TZP1(uint8_t wait) {
  int r = 0;
  int g = 0;
  int b = 255;

  for (int j = 0; j < 100; j++) { //do 10 cycles of chasing
    if (j < 50) {
      b -= 40;
      //      r+=20;
      g += 5;
    }
    else {
      b += 40;
      //      r-=20;
      g -= 5;
    }
    uint32_t c = strip.Color(r, g, b);
    for (int q = 0; q < 6; q += 3) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 6) {
        strip.setPixelColor(i + q, c);  //turn every __ pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 6) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}
void TZP2(uint16_t n, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels() + n; i++) {
    strip.setPixelColor(i, strip.Color(127, 127, 127));
    strip.setPixelColor(i - n, strip.Color(0, 0, 0));
    strip.show();
    delay(wait);
  }
}
void TZP3(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, chaseWheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}
void TZP4(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) {
    uint16_t onLed [4];
    for (int i = 0; i < 4; i++) {
      onLed[i] = random(0, 120);
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        strip.setPixelColor(onLed[i] + j, c);
      }

    }
    strip.show();
    delay(wait);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        strip.setPixelColor(onLed[i] + j, 0);
      }
    }
  }
}
void TZP5(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, rainbowWheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
//--------------------MOM--------------------//
void MOM1(uint16_t n, uint8_t wait) {
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < strip.numPixels() + n; i++) {
      strip.setPixelColor(i, MOMWheel((i + j) & 255));
      strip.setPixelColor(i - n, strip.Color(0, 0, 0));
      strip.show();
      delay(wait);
    }
  }
}
uint32_t MOMWheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void MOM2(uint8_t wait) {

  for (int i = 0; i < 120; i += 60) {
    //    k-=10;
    int l = 127;
    int m = 0;

    for (int k = 0; k < 127; k++) {

      for (int j = i; j < i + 60; j++) {
        strip.setPixelColor(j, strip.Color(m, m, m));
      }

      strip.show();

      delay(10);
      m += 1;
    }
    
    for (int k = 0; k < 127; k++) {

      for (int j = i; j < i + 60; j++) {
        strip.setPixelColor(j, strip.Color(l, l, l));
      }

      strip.show();

      delay(10);
      l -= 1;
    }

    for (int j = i; j < i + 60; j++) {
      strip.setPixelColor(j, 0);

    }
  }
}
void mytest(uint32_t c, uint8_t wait) {

  for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
    strip.setPixelColor(i , c);  //turn every third pixel on
  }
  strip.show();

  delay(wait);



}


