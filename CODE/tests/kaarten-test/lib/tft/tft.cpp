/**
 * @file tft.cpp
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief TFT definition and functions
 * @version 0.2.3
 * @date 2025-06
 */

#include "tft.hpp"

TFT_eSPI tft = TFT_eSPI();
bool repeatCalib = false;
bool waitScreenRefresh = false;



/**
 * @brief Init TFT display
 *
 * @details Initializes the TFT display,
 */
void initTFT()
{
	tft.init();
	
	#ifdef TDECK_ESP32S3
		tft.setRotation(1);
	#endif

	TFT_HEIGHT = tft.height();
	TFT_WIDTH = tft.width();

	tft.initDMA();
	tft.fillScreen(TFT_BLACK);
}
