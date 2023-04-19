#include <FastLED.h>
#include <Keypad.h>

#define LED_PIN null
#define NUM_LEDS 100

CRGB leds[NUM_LEDS];


  //Gets the individual numpad buttons
char keypad[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

short rowPins[4] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
short colPins[4] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

int colors[4][3] = {
    {200, 200, 200},
    {100, 100, 100},
    {50, 50, 50},
    {50, 100, 200}
} ;

// List of colors for the gradient on testLEDs()
int gradientA[21][3] = {
    {153, 0, 76},
    {204, 0, 102},
    {255, 51, 51},
    {255, 0, 0},
    {255, 153, 51},
    {255, 128, 0},
    {255, 255, 51},
    {128, 255, 0},
    {51, 255, 51},
    {0, 255, 128},
    {0, 153, 76},
    {51, 255, 255},
    {0, 255, 255},
    {102, 178, 255},
    {0, 128, 255},
    {0, 76, 153},
    {0, 0, 153},
    {0, 0, 102},
    {102, 0, 204},
    {76, 0, 153},
    {51, 0, 102}
} ;

Keypad membraneKeypad;

/**This is to test the LEDs. It will go through the gradientA array and set the LEDs to the colors in the array. 
*@param numLEDS is the number of LEDs you would like to test.
*Currently configured to test LEDs that have GRB color order (for some reason).
*/
void testLEDs(int numLEDS){ 
    for(int q = 0; q < 21; q++){
        for(int i = 0; i < numLEDS; i++){
            leds[i] = CRGB(gradientA[q][1], gradientA[q][0], gradientA[q][2]);
            FastLED.show();
            delay((3)); //This cycles the LED's to make it a nice gradient. The delay is in milliseconds.
        }
        delay(500);
    }
    fill_solid(leds, NUM_LEDS, CRGB(0,255,0));
    delay(2000);
}

// This does an auto  gradient. It takes in the number of LEDs, the colors, the delay time, and the period (ie. how long it takes to go through the gradient(cycles). If it was 1 it would go through the gradient one time per strip.
/**
 * This is a function that will do an auto gradient.
 * @param numLeds is the number of LEDs in the stri
 * @param colors is the 2D array of colors that you want to use in the gradient.
 * @param delayTime is the time in milliseconds that you want to wait between each LED lighting up.
 * @param period is the number of times you would like to cycle through the colors per @param numleds leds.
*/

void autoGradient(int numLeds, int[numOfLeds][3] colors, int delayTime, float period){
    int totColors = sizeof colors / sizeof colors[0];   //This is to get the total number of colors in the array
    int CPP = numLeds / totColors; //This is to get the number of LEDs per color
    int DBCP = (int)(period * CPP); // This
    int rt = 0;
    for(int q = 0; q< totColors; q++){
        for(rt; rt < numLeds; rt+=DBCP){
            for(int j = 0; j<DBCP; j++){
                leds[rt+j] = CRGB(colors[q][0], colors[q][1], colors[q][2]);
                FastLED.show();
                delay(delayTime);
            }
        }
    }           

}



void setup(){
    Serial.begin(9600);
    membraneKeypad = Keypad( makeKeymap(keypad), rowPins, colPins, 4, 4); //Creates the keypad

    //This is to make sure that the colors are not out of range
    for(int i = 0; i < sizeof colors / sizeof colors[0]; i++){
        for(int j = 0; j< sizeof colors[0] / sizeof(int); j++){
            if(colors[i][j] > 256){
                colors[i][j] = 256;
            }else if(colors[i][j] < 0){
                colors[i][j] = 0;
            }
        }
    }

    //Here we are adding the leds. The first number is the type of led, so in this case WS2812B. The second is the pin, and the third is the color order.
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255);

    testLEDs(NUM_LEDS);
    FastLED.clear();  // clear all pixel data
    FastLED.show();
}

void loop(){
    char customKey = membraneKeypad.getKey(); // This is to get the key that is pressed, if no key is pressed it will return NO_KEY. This is kind of like getButtonPressed() in the other code

    switch (customKey){
        case 'NO_KEY':
            Serial.println("No key is being pressed");
            break;
        case '1':
            Serial.println("1 is being pressed");
            leds[0] = CRGB(colors[0][1],colors[0][0], colors[0][2]);
            FastLED.show();
            break;
        case '2':
            Serial.println("2 is being pressed");
            leds[0] = CRGB(colors[1][1],colors[1][0], colors[1][2]);
            FastLED.show();
            break;
        case '3':
            Serial.println("3 is being pressed");
            leds[0] = CRGB(colors[2][1],colors[2][0], colors[2][2]);
            FastLED.show();
            break;
        case '4':
            Serial.println("4 is being pressed");
            leds[0] = CRGB(colors[3][1],colors[3][0], colors[3][2]);
            FastLed.show();
            break;
        case 'A':
            Serial.println("A is being pressed");
            autoGradient(NUM_LEDS, colors, 3, 1);
            break;
    }


}