#pragma once

#include <Arduino.h>   

#include <lvgl.h>
#include "tft.hpp"
#include "homeScreen.hpp"
#include "globalGuiDef.h"

#define TOUCH_MAX_POINTS 5

void IRAM_ATTR displayFlush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);
void IRAM_ATTR touchReadLVGL(lv_indev_t *indev_driver, lv_indev_data_t *data);
void initLVGL();
void makeTestScreen();
static void btn_event_cb(lv_event_t * e);
