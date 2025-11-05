#include "lvglSetup.hpp"

lv_display_t* display;

// flush functie zorgt ervoor dat de buffer die in ram zit naar het scherm verzonden word.
// Dit is een callback, deze functie wordt door lvgl zelf aangeroepen wanneer er een flush nodig is.
// IRAM_ATTR plaats functie in RAM en voer vanaf daar uit.
// Hierdoor kan deze functie sneller uitgevoerd worden.

void IRAM_ATTR displayFlush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) 
{ 
  uint32_t w = (area->x2 - area->x1 + 1); // Breedte van het gebied dat geüpdatet moet worden
  uint32_t h = (area->y2 - area->y1 + 1); // Hoogte van het gebied dat geüpdatet moet worden

  tft.setSwapBytes(true); // Zet byte swapping aan voor juiste kleurweergave
  tft.setAddrWindow(area->x1, area->y1, w, h); // Stel het adresvenster in op het gebied dat geüpdatet moet worden
  tft.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (uint16_t*)px_map); // Stuur de pixeldata naar het scherm via DMA
  tft.setSwapBytes(false); // Zet byte swapping weer uit

  lv_display_flush_ready(disp); // Geef aan lvgl door dat de flush voltooid is
}

// Functie om de touchscreen data uit te lezen en door te geven aan lvgl.
// Dit is ook een callback functie die door lvgl zelf wordt aangeroepen wanneer er touchscreen data nodig is.

void IRAM_ATTR touchReadLVGL(lv_indev_t *indev_driver, lv_indev_data_t *data){
  lgfx::touch_point_t touchRaw[TOUCH_MAX_POINTS]; // Array om de ruwe touch data in op te slaan
	static lgfx::touch_point_t touchPrev[TOUCH_MAX_POINTS]; // Array om de vorige touch data in op te slaan
	static unsigned long lastTime = 0; // Variabele om de tijd van de laatste update bij te houden

	int count = tft.getTouch(touchRaw, TOUCH_MAX_POINTS); // Lees de touch data uit het TFT object

	unsigned long now = millis(); 
	float dt_ms = (now > lastTime) ? (float)(now - lastTime) : 1.0f; // Bereken de tijd sinds de laatste update

  if(count == 0){ // Geen aanraking gedetecteerd
    data->state = LV_INDEV_STATE_RELEASED;
  } else if(count == 1) { // Eén aanraking gedetecteerd
    data->point.x = touchRaw[0].x; // Stel de x en y coördinaten in
    data->point.y = touchRaw[0].y;
    data->state = LV_INDEV_STATE_PRESSED; // Zet de state op pressed
  }
}

// Functie om LVGL te initialiseren en te koppelen aan het TFT scherm en touchscreen.
void initLVGL() {
    lv_init();

    display = lv_display_create(TFT_WIDTH, TFT_HEIGHT); // maakt een display object aan met de resolutie van het TFT scherm
    lv_display_set_flush_cb(display, displayFlush); // koppelt de flush callback functie aan het display object
    lv_display_set_flush_wait_cb(display, NULL); // geen wait callback nodig

    size_t buf_size = TFT_WIDTH * TFT_HEIGHT * sizeof(uint16_t); // buffer grootte voor volledige scherm

    lv_color_t *buf1 = (lv_color_t *)heap_caps_aligned_alloc(16, buf_size, MALLOC_CAP_SPIRAM); // Eerste buffer in PSRAM
    lv_color_t *buf2 = (lv_color_t *)heap_caps_aligned_alloc(16, buf_size, MALLOC_CAP_SPIRAM); // Tweede buffer in PSRAM

    // Twee buffers zorgen ervoor dat er geen slechte data op het scherm verschijnt tijdens het updaten van het scherm.
    lv_display_set_buffers(display, buf1, buf2, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

    // extra setup voor touchscreen
    lv_indev_t *touch_input = lv_indev_create(); // maakt een input device aan voor het touchscreen
    lv_indev_set_type(touch_input, LV_INDEV_TYPE_POINTER);  // zet het type van het input device op pointer(touchscreen)

    lv_indev_set_read_cb(touch_input, touchReadLVGL); // koppelt de touch read callback functie aan het input device

    makeHomeScreen();
}


static void btn_event_cb(lv_event_t * e) // Event callback functie voor de knop
{
  lv_event_code_t code = lv_event_get_code(e); // Haal de event code op
  lv_obj_t * btn = lv_event_get_target_obj(e); // Haal het object op dat het event heeft getriggerd
  if(code == LV_EVENT_CLICKED) { // Als de knop is aangeklikt
    static uint8_t cnt = 0;
    cnt++;

    lv_obj_t * label = lv_obj_get_child(btn, 0); // Haal het label op dat kind is van de knop
    lv_label_set_text_fmt(label, "Button: %d", cnt); // Update de tekst van het label met het aantal keer dat de knop is aangeklikt
  }
}

void loadHomeScreen(){
  lv_screen_load(homeScreen); // Laad het home screen
}