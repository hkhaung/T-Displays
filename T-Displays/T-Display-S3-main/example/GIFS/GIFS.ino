#include <AnimatedGIF.h>
#include <OneButton.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "fatyoshi.h"
#include "fatyoshi1.h"
#include "girlbreadrun.h"
#include "mecharunning.h"
#include "unit01.h"

#define PIN_POWER_ON 15 
#define PIN_LCD_BL 38
#define DISPLAY_PIN 0
#define BUTTON_PIN 14
#define IMAGE_WIDTH  240    // Width of the image for starting screen
#define IMAGE_HEIGHT 320    // Height of the image for starting screen
#define GIF_IMAGE girlbreadrun
#define DEBOUNCE_TIME 200 // in milliseconds

TFT_eSPI tft = TFT_eSPI();
unsigned long gifStartTime = 0;
unsigned long initialDisplayDuration = 2000; // Display initial image for 2000 ms (2 seconds)
AnimatedGIF gif;
int currentGif = 0;
bool displayState = true;


void setup() {
	pinMode(PIN_POWER_ON, OUTPUT);  //enables the LCD and to run on battery
	pinMode(PIN_LCD_BL, OUTPUT);    //controls the LCD backlight
	digitalWrite(PIN_POWER_ON, HIGH);
	digitalWrite(PIN_LCD_BL, HIGH);

	Serial.begin(115200);
	tft.begin();
	tft.setRotation(0);
	tft.fillScreen(TFT_BLACK);
	tft.setSwapBytes(true);
	delay(200);
	tft.pushImage(-35, 20, IMAGE_WIDTH, IMAGE_HEIGHT, fatyoshi1);
	gifStartTime = millis();
}


void playGIF(int gifIndex) {
	uint8_t *gifData;
	size_t gifSize;
	switch (gifIndex) {
		case 0:
			gifData = (uint8_t *)girlbreadrun;
			gifSize = sizeof(girlbreadrun);
			break;
		case 1:
			gifData = (uint8_t *)mecharunning;
			gifSize = sizeof(mecharunning);
			break;
		case 2:
			gifData = (uint8_t *)unit01;
			gifSize = sizeof(unit01);
			break;
	}

	if (gif.open(gifData, gifSize, GIFDraw)) { // Open GIF from RAM
		Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
		tft.startWrite(); // The TFT chip select is locked low
		while (gif.playFrame(true, NULL)) {
				yield();
		}
		gif.close();
		tft.endWrite();
	} else {
		Serial.println("Failed to open GIF");
	}
}

static unsigned long lastButtonPressGIF = 0;
static unsigned long lastButtonPressPower = 0;

void loop() {
	if (digitalRead(BUTTON_PIN) == LOW) {
		if (millis() - gifStartTime > initialDisplayDuration) { // Only allow button input after initial image has been displayed for its duration
			if (millis() - lastButtonPressGIF > DEBOUNCE_TIME) { // Debounce button
				lastButtonPressGIF = millis();
				currentGif = (currentGif + 1) % 3;
			}
		}
	} 

	if (millis() - gifStartTime > initialDisplayDuration) {
    	playGIF(currentGif);
	}

	if (digitalRead(DISPLAY_PIN) == LOW) {
		if (millis() - lastButtonPressPower > DEBOUNCE_TIME) {
			lastButtonPressPower = millis();
			Serial.println("power button pressed");
			displayState = !displayState;
			digitalWrite(PIN_LCD_BL, displayState);
		}
	}
	
}
