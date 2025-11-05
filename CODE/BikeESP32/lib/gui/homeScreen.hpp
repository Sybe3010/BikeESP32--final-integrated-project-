#pragma once

#include "globalGuiDef.h"

extern lv_obj_t *homeTile;
extern lv_obj_t *settingTile; // staat boven de homeTile
extern lv_obj_t *optionsTile; // staat onder de homeTile

// Tiles voor de keuze activiteiten scherm
extern lv_obj_t *activityTiles;
extern lv_obj_t *roadActivityTile;
extern lv_obj_t *gravelActivityTile;
extern lv_obj_t *mtbActivityTile;

//knoppen voor activiteiten keuze scherm
extern lv_obj_t *roadActivityBtn;
extern lv_obj_t *gravelActivityBtn;
extern lv_obj_t *mtbActivityBtn;

// knoppen
extern lv_obj_t *navigationButton;
extern lv_obj_t *optionsButton;
extern lv_obj_t *settingsButton;

// knoppen voor settingsScreen
extern lv_obj_t *nightDayButton;
extern lv_obj_t *accountButton;
extern lv_obj_t *bluetoothButton;
extern lv_obj_t *moreSettingsButton;
//extern lv_obj_t *wifiToggle;

void navBtnEvent(lv_event_t * e);
void optionsBtnEvent(lv_event_t * e);
void settingsBtnEvent(lv_event_t * e);

void nightDayBtnEvent(lv_event_t * e);
void accountBtnEvent(lv_event_t * e);
void bluetoothBtnEvent(lv_event_t * e);
void moreSettingsBtnEvent(lv_event_t * e);

void makeHomeScreen();