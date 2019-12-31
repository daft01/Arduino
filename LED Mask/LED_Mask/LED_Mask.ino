#include "FastLED.h"
#include "IRremote.h"

// How many leds in your strip?
#define NUM_LEDS 82
#define DATA_PIN 2
#define FORWARD 0
#define BACKWARD 1
#define SLOW 250
#define MEDIUM 50
#define FAST 5
#define HEIGHT 6
#define WIDTH  6
#define MASK_WIDTH 11
CRGB leds[NUM_LEDS];
boolean direction = FORWARD;
int current = 16748655;

// Control
int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

signed char letters[26][HEIGHT][WIDTH] = {
                      {{0,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,1,1,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}}, // A
                      {{1,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,1,1,0,0,-1}}, // B
                      {{0,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,0,0,-1}, {1,0,0,0,0,-1}, {1,0,0,1,0,-1}, {0,1,1,0,0,-1}}, // C
                      {{1,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,1,1,0,0,-1}}, // D
                      {{1,1,1,1,0,-1}, {1,0,0,0,0,-1}, {1,1,1,0,0,-1}, {1,0,0,0,0,-1}, {1,0,0,0,0,-1}, {1,1,1,1,0,-1}}, // E
                      {{1,1,1,1,0,-1}, {1,0,0,0,0,-1}, {1,1,1,0,0,-1}, {1,0,0,0,0,-1}, {1,0,0,0,0,-1}, {1,0,0,0,0,-1}}, // F
                      {{0,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,0,0,-1}, {1,0,1,1,0,-1}, {1,0,0,1,0,-1}, {0,1,1,0,0,-1}}, // G
                      {{1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,1,1,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}}, // H
                      {{1,1,1,1,1,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}, {1,1,1,1,1,0}},       // I
                      {{0,0,0,1,0,-1}, {0,0,0,1,0,-1}, {0,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {0,1,1,0,0,-1}}, // J
                      {{1,0,0,1,0,-1}, {1,0,1,0,0,-1}, {1,1,0,0,0,-1}, {1,0,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}}, // k
                      {{1,0,0,0,0,-1}, {1,0,0,0,0,-1}, {1,0,0,0,0,-1}, {1,0,0,0,0,-1}, {1,0,0,0,0,-1}, {1,1,1,1,0,-1}}, // L
                      {{1,0,0,0,1,0}, {1,1,0,1,1,0}, {1,0,1,0,1,0}, {1,0,0,0,1,0}, {1,0,0,0,1,0}, {1,0,0,0,1,0}},       // M
                      {{1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,1,0,1,0,-1}, {1,0,1,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}}, // N
                      {{0,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {0,1,1,0,0,-1}}, // O
                      {{1,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,1,1,0,0,-1}, {1,0,0,0,0,-1}, {1,0,0,0,0,-1}}, // P
                      {{0,1,1,0,0,0}, {1,0,0,1,0,0}, {1,0,0,1,0,0}, {1,0,0,1,0,0}, {1,0,0,1,0,0}, {0,1,1,1,1,0}},       // Q
                      {{1,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}}, // R
                      {{0,1,1,0,0,-1}, {1,0,0,1,0,-1}, {0,1,0,0,0,-1}, {0,0,1,0,0,-1}, {1,0,0,1,0,-1}, {0,1,1,0,0,-1}}, // S
                      {{1,1,1,1,1,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}},       //T
                      {{1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,1,1,1,0,-1}}, //U
                      {{1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {0,1,1,0,0,-1}}, //V
                      {{1,0,0,0,1,0}, {1,0,0,0,1,0}, {1,0,0,0,1,0}, {1,0,1,0,1,0}, {1,0,1,0,1,0}, {0,1,0,1,0,0}},       //W
                      {{1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {0,1,1,0,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}, {1,0,0,1,0,-1}}, //X
                      {{1,0,0,0,1,0}, {1,0,0,0,1,0}, {0,1,0,1,0,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}, {0,0,1,0,0,0}},//Y
                      {{1,1,1,1,0,-1}, {0,0,0,1,0,-1}, {0,0,1,0,0,-1}, {0,1,0,0,0,-1}, {1,0,0,0,0,-1}, {1,1,1,1,0,-1}}  //Z
                    };

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  randomSeed(analogRead(0));

  irrecv.enableIRIn(); // Start the control receiver
  
  Serial.begin(9600);
}

void loop() { 

  if (irrecv.decode(&results)) {
    Serial.println("lol");
    current = results.value;
    disolve(50,100, 5);
    irrecv.resume();
  }

  switch(current){
    case 16753245:
      Serial.println("CH-");
      break;
    case 16736925:
      Serial.println("CH");
      break;
    case 16769565:
      Serial.println("CH+");
      break;
    case 16720605:
      Serial.println("PREV");
      break;
    case 16712445:
      Serial.println("NEXT");
      break;
    case 16761405:
      Serial.println("PLAY/PAUSE");
      break;
    case 16769055:
      Serial.println("-");
      break;
    case 16754775:
      Serial.println("+");
      break;
    case 16748655:
      Serial.println("EQ"); // Snails text
      displayText("snails", CRGB::Red, 65);
      break;
    case 16738455:
      Serial.println("0");  // Theater Chase Rainbow
      theaterChaseRainbow(1,MEDIUM);
      break;
    case 16750695:
      Serial.println("100+"); 
      break;
    case 16756815:
      Serial.println("200+");
      break;
    case 16724175:
      Serial.println("1"); //Cylon
      cylon(randomColor(), 10,FAST);
      break;
    case 16718055:
      Serial.println("2"); // Rainbow
      rainbow(0,NULL); 
      break;
    case 16743045:
      Serial.println("3");  // Lightning
      lightning(NULL,50,100,MEDIUM);
      break;
    case 16716015:
      Serial.println("4"); // Flash
      flash(NULL,100,MEDIUM);
      break;
    case 16726215:
      Serial.println("5"); // Color Wipe
      colorWipe(randomColor(),FAST);
      break;
    case 16734885:
      Serial.println("6");
      displayText("snails", CRGB::Red, 65);
      rainbow(0,NULL);
      cylon(randomColor(), 10,FAST);
      lightning(NULL,50,100,MEDIUM);
      theaterChaseRainbow(1,MEDIUM);
      rainbow(FAST,1);
      disolve(50,100,FAST);
      flash(NULL,100,MEDIUM);
      colorWipe(randomColor(),FAST);
      break;
    case 16728765:
      Serial.println("7");
      break;
    case 16730805:
      Serial.println("8");
      break;
    case 16732845:
      Serial.println("9");
      break;
  }
  
  Serial.println(current);
  
//  displayText("snails", CRGB::Red, 200);
//  rainbow(0,NULL);
//  cylon(randomColor(), 10,FAST);
//  lightning(NULL,50,100,MEDIUM);
//  theaterChaseRainbow(1,MEDIUM);
//  rainbow(FAST,1);
//  disolve(50,100,FAST);
//  flash(NULL,100,MEDIUM);
//  colorWipe(randomColor(),FAST);
 
}

// Changes all LEDS to given color
void allColor(CRGB c){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = c;
  }
  FastLED.show();
}

void allRandom(){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = randomColor();
  }
  FastLED.show(); 
}

// Random disolve colors
void disolve(int simultaneous, int cycles, int speed){
  for(int i=0; i<cycles; i++){
    for(int j=0; j<simultaneous; j++){
      int idx = random(NUM_LEDS);
      leds[idx] = CRGB::Black;
    }
    FastLED.show();
    delay(speed);
  }

  allColor(CRGB::Black);
}

// Flashes given color
// If c==NULL, random color flash
void flash(CRGB c, int count, int speed){
  for(int i=0; i<count; i++){
    if(c){
      allColor(c);
    }
    else{
      allColor(randomColor());
    }
    delay(speed);
    allColor(CRGB::Black);
    delay(speed);
  }
}

// Wipes color from end to end
void colorWipe(CRGB c, int speed){
  for(int i=0; i<NUM_LEDS; i++){
    if(direction == FORWARD){
      leds[i] = c;
    }
    else{
      leds[NUM_LEDS-1-i] = c;
    }
    FastLED.show();
    delay(speed);
  }

  direction = !direction;
}

// Rainbow colors that slowly cycle across LEDs
void rainbow(int cycles, int speed){ // TODO direction
  if(cycles == 0){
    for(int i=0; i< NUM_LEDS; i++) {
      leds[i] = Wheel(((i * 256 / NUM_LEDS)) & 255);
    }
    FastLED.show();
  }
  else{
    for(int j=0; j<256*cycles; j++) {
      for(int i=0; i< NUM_LEDS; i++) {
        leds[i] = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      }
      FastLED.show();
      delay(speed);
    }
  }
}

// Theater-style crawling lights
void theaterChase(CRGB c, int cycles, int speed){ // TODO direction

  for (int j=0; j<cycles; j++) {  
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        int pos = i+q;
        leds[pos] = c;    //turn every third pixel on
      }
      FastLED.show();

      delay(speed);

      for (int i=0; i < NUM_LEDS; i=i+3) {
        leds[i+q] = CRGB::Black;        //turn every third pixel off
      }
    }
  }
}

// Theater-style crawling lights with rainbow effect
void theaterChaseRainbow(int cycles, int speed){ // TODO direction, duration
  for (int j=0; j < 256 * cycles; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        int pos = i+q;
        leds[pos] = Wheel( (i+j) % 255);    //turn every third pixel on
      }
      FastLED.show();

      delay(speed);

      for (int i=0; i < NUM_LEDS; i=i+3) {
        leds[i+q] = CRGB::Black;  //turn every third pixel off
      }
    }
  }
}

// Random flashes of lightning
void lightning(CRGB c, int simultaneous, int cycles, int speed){
  int flashes[simultaneous];

  for(int i=0; i<cycles; i++){
    for(int j=0; j<simultaneous; j++){
      int idx = random(NUM_LEDS);
      flashes[j] = idx;
      leds[idx] = c ? c : randomColor();
    }
    FastLED.show();
    delay(speed);
    for(int s=0; s<simultaneous; s++){
      leds[flashes[s]] = CRGB::Black;
    }
    delay(speed);
  }
}

// Sliding bar across LEDs
void cylon(CRGB c, int width, int speed){
  // First slide the leds in one direction
  for(int i = 0; i <= NUM_LEDS-width; i++) {
    for(int j=0; j<width; j++){
      leds[i+j] = c;
    }

    FastLED.show();

    // now that we've shown the leds, reset to black for next loop
    for(int j=0; j<5; j++){
      leds[i+j] = CRGB::Black;
    }
    delay(speed);
  }

  // Now go in the other direction.  
  for(int i = NUM_LEDS-width; i >= 0; i--) {
    for(int j=0; j<width; j++){
      leds[i+j] = c;
    }
    FastLED.show();
    for(int j=0; j<width; j++){
      leds[i+j] = CRGB::Black;
    }

    delay(speed);
  }
}

// Display alternating stripes
void stripes(CRGB c1, CRGB c2, int width){
  for(int i=0; i<NUM_LEDS; i++){
    if(i % (width * 2) < width){
      leds[i] = c1;
    }
    else{
      leds[i] = c2;
    } 
  }
  FastLED.show();
}

// Theater-style crawling of stripes
void stripesChase(CRGB c1, CRGB c2, int width, int cycles, int speed){ // TODO direction

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

CRGB randomColor(){
  return Wheel(random(256)); 
}

void displayText(char str[], CRGB color, int delayTime){

    for (int i = 0; i < strlen(str); i++){

        int index = str[i] - 'a';

        int tempWidth = WIDTH;

        if(letters[index][0][WIDTH-1])
          tempWidth--;

        for(int w=0; w<tempWidth; w++){

            moveText();
  
              for(int h=0; h<HEIGHT; h++){
  
                  if(letters[index][h][w] == 1){
                      if(h%2 == 0){
                          leds[MASK_WIDTH+MASK_WIDTH*h-1] = color;
                      }else{
                          leds[MASK_WIDTH*h]  = color;
                      }
                  }else {
                      if(h%2 == 0){
                          leds[MASK_WIDTH+MASK_WIDTH*h-1] = CRGB::Black;
                      }else{
                          leds[MASK_WIDTH*h]  = CRGB::Black;
                      }
                  }
              }
  
              FastLED.show();
              delay(delayTime);
        }
    }

    for(int i=0; i<11; i++){
      moveText();
      FastLED.show();
      delay(delayTime);
    }
}

void moveText(){

    int row;
    int w = MASK_WIDTH;
    int temp;
  
    for(int i=0; i<NUM_LEDS; i++){
  
        row = i/w;
        
        if( ( row%2 == 0) )
            leds[i] = leds[i+1];
    }
  
    for(int i=NUM_LEDS-1; i>0; i--){
        row = i/w;
          
        if( ( row%2 != 0) )
            leds[i] = leds[i-1];
    }
  
}
