#pragma once

#include <Arduino.h>

#include "panel.hpp"

#include <LGFX_TFT_eSPI.hpp>

extern TFT_eSPI tft;                                      /**< TFT display object */

uint16_t TFT_WIDTH = 128;                               /**< TFT display width in pixels */
uint16_t TFT_HEIGHT = 160;                              /**< TFT display height in pixels */
bool waitScreenRefresh;                           /**< Wait for refresh screen  */

void initTFT();

