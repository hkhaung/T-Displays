#include "rm67162.h"
#include "TFT_eSPI.h"
#include <lvgl.h>
#include <OneButton.h>

#include "fatyoshi.h"

LV_IMG_DECLARE(blinkinguyAMOLED);
LV_IMG_DECLARE(homerbushAMOLED);
LV_IMG_DECLARE(huhcatAMOLED);

TFT_eSPI tft= TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

OneButton button1(PIN_BUTTON_1, true);
OneButton button2(PIN_BUTTON_2, true);

bool displayOn = true;

int currentGifIndex = 0;
lv_obj_t *currentGif = nullptr;

void setup() {
  lv_init();
  tft.begin();
  setup_lvgl_display();
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);

  rm67162_init(); // amoled lcd initialization
  lcd_setRotation(0);

  sprite.createSprite(TFT_WIDTH, TFT_HEIGHT);
  sprite.fillScreen(TFT_WHITE);
  sprite.setSwapBytes(true);
  sprite.pushImage(0, 0, TFT_WIDTH, TFT_HEIGHT, fatyoshi);
  lcd_PushColors(0, 0, TFT_WIDTH, TFT_HEIGHT, (uint16_t*)sprite.getPointer());
  sprite.setSwapBytes(false);
  
  delay(5000);

  button1.attachClick(turnDisplayOff);
  button2.attachClick(nextGif);
  displayGif(0);
}

void setup_lvgl_display() {
    static lv_color_t buf[LVGL_LCD_BUF_SIZE];  // Buffer for LVGL drawing operations
    static lv_disp_draw_buf_t draw_buf;

    // Initialize the display buffer for LVGL
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, LVGL_LCD_BUF_SIZE);  // Initialize the display buffer

    static lv_disp_drv_t disp_drv;  // Create a display driver
    lv_disp_drv_init(&disp_drv);  // Basic initialization

    // Set up your specific display flushing function
    disp_drv.flush_cb = my_disp_flush;  
    disp_drv.draw_buf = &draw_buf;  // Set the display buffer
    disp_drv.hor_res = EXAMPLE_LCD_V_RES;  // Horizontal resolution, set according to your display
    disp_drv.ver_res = EXAMPLE_LCD_H_RES;  // Vertical resolution, set according to your display

    lv_disp_drv_register(&disp_drv);  // Register the driver with LVGL
}

void my_disp_flush(lv_disp_drv_t *disp,
                   const lv_area_t *area,
                   lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    lcd_PushColors(area->x1, area->y1, w, h, (uint16_t *)&color_p->full);
    lv_disp_flush_ready(disp);
}

void turnDisplayOff() {
    if (displayOn) {
        // Assuming you can turn off the display by controlling backlight or power pin
        digitalWrite(PIN_LED, LOW);  // Turn off the backlight if used
        displayOn = false;
    } else {
        digitalWrite(PIN_LED, HIGH); // Turn on the backlight if used
        displayOn = true;
    }
}

void nextGif() {
    currentGifIndex = (currentGifIndex + 1) % 3;
    displayGif(currentGifIndex);
}

void displayGif(int index) {
    if (currentGif) {
        lv_obj_del(currentGif);  // Remove the old GIF before displaying a new one
    }

    currentGif = lv_gif_create(lv_scr_act());
    lv_gif_set_src(currentGif, &homerbushAMOLED);
    switch (index) {
      case 0:
        lv_gif_set_src(currentGif, &homerbushAMOLED);
        break;
      case 1:
        lv_gif_set_src(currentGif, &blinkinguyAMOLED);
        break;
      case 2:
        lv_gif_set_src(currentGif, &huhcatAMOLED);
        break;
    }
    lv_obj_center(currentGif);
}

void loop() {
  button1.tick();
  button2.tick();
  lv_timer_handler(); // Handle LVGL tasks
  delay(5);
}