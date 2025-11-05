#include "tft.hpp"

TFT_eSPI tft = TFT_eSPI();

uint16_t TFT_WIDTH = 0;
uint16_t TFT_HEIGHT = 0;


void initTFT()
{
	tft.init();

	TFT_HEIGHT = tft.height();
	TFT_WIDTH = tft.width();

	tft.initDMA();
	tft.fillScreen(TFT_BLACK);

}