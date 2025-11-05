#pragma once

#include <Arduino.h>

#include "display.hpp"

#include <LGFX_TFT_eSPI.hpp>

extern TFT_eSPI tft;                                                         

extern uint16_t TFT_WIDTH;                               
extern uint16_t TFT_HEIGHT;                              

void initTFT();