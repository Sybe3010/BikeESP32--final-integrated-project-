#include "homeScreen.hpp"

void navBtnEvent(lv_event_t * e){
    // Nav button event handler
    // Laad het navigatiescherm of voer een actie uit
}
void optionsBtnEvent(lv_event_t * e){
    // Options button event handler
    // Laad het optiescherm of voer een actie uit
}
void settingsBtnEvent(lv_event_t * e){
    // Settings button event handler
    // Laad het instellingen scherm of voer een actie uit
}

void nightDayBtnEvent(lv_event_t * e){
    // Night/Day button event handler
}
void accountBtnEvent(lv_event_t * e){
    // Account button event handler
}
void bluetoothBtnEvent(lv_event_t * e){
    // Bluetooth button event handler
}
void moreSettingsBtnEvent(lv_event_t * e){
    // More Settings button event handler
}

void makeHomeScreen(){
    homeScreen = lv_obj_create(NULL); // Maak een nieuw scherm object aan

    // HomeScreen Tiles
    homeScreenTiles = lv_obj_create(homeScreen); // Maak een container voor de tegels op het homescreen
    settingTile = lv_tileview_add_tile(homeScreenTiles, 0, -1, LV_DIR_TOP); // Voeg de instellingentegel toe boven de homeTile
    homeTile = lv_tileview_add_tile(homeScreenTiles, 0, 0, (lv_dir_t)(LV_DIR_TOP | LV_DIR_BOTTOM)); // Voeg de homeTile toe in het midden
    optionsTile = lv_tileview_add_tile(homeScreenTiles, 0, 1, LV_DIR_BOTTOM); // Voeg de optieentegel toe onder de homeTile
    lv_obj_set_size(homeScreenTiles, lv_disp_get_hor_res(display) , lv_disp_get_ver_res(display) - 25); //-25 om ruimte te laten voor de statusbalk
    lv_obj_set_pos(homeScreenTiles, 0, 25);

    // Activiteiten keuze scherm tiles
    activityTiles = lv_obj_create(homeTile); // Maak een container voor de tegels op het activiteiten keuze scherm
    roadActivityTile = lv_tileview_add_tile(activityTiles, 0, 0, LV_DIR_LEFT); 
    gravelActivityTile = lv_tileview_add_tile(activityTiles, 1, 0, (lv_dir_t)(LV_DIR_LEFT | LV_DIR_RIGHT)); 
    mtbActivityTile = lv_tileview_add_tile(activityTiles, 2, 0, LV_DIR_RIGHT);
    lv_obj_set_size(activityTiles, 300 , 188); //-20 en -35 om ruimte te laten voor de marges en statusbalk
    lv_obj_set_pos(activityTiles, 10, 10);
    
    //Maak activity tiles inhoud
    roadActivityBtn = lv_btn_create(roadActivityTile);
    lv_obj_set_size(roadActivityBtn, 300, 188);
    lv_obj_set_pos(roadActivityBtn, 0, 0);
    lv_obj_t* roadLabel = lv_label_create(roadActivityBtn);
    lv_label_set_text(roadLabel, "Road");
    lv_obj_set_pos(roadLabel, 10, 30);

    gravelActivityBtn = lv_btn_create(gravelActivityTile);
    lv_obj_set_size(gravelActivityBtn, 300, 188);
    lv_obj_set_pos(gravelActivityBtn, 0, 0);
    lv_obj_t* gravelLabel = lv_label_create(gravelActivityBtn);
    lv_label_set_text(gravelLabel, "Gravel");
    lv_obj_set_pos(gravelLabel, 10, 30);

    mtbActivityBtn = lv_btn_create(mtbActivityTile);
    lv_obj_set_size(mtbActivityBtn, 300, 188);
    lv_obj_set_pos(mtbActivityBtn, 0, 0);
    lv_obj_t* mtbLabel = lv_label_create(mtbActivityBtn);
    lv_label_set_text(mtbLabel, "Mountainbike");
    lv_obj_set_pos(mtbLabel, 10, 30);

    // Add homeScreen buttons
    navigationButton = lv_btn_create(homeScreenTiles);
    lv_obj_set_size(navigationButton, 75, 75);
    lv_obj_set_pos(navigationButton, 308, 32);

    optionsButton = lv_btn_create(homeScreenTiles);
    lv_obj_set_size(optionsButton, 75, 75);
    lv_obj_set_pos(optionsButton, 308, 123);
    
    settingsButton = lv_btn_create(homeScreenTiles);
    lv_obj_set_size(settingsButton, 75, 75);
    lv_obj_set_pos(settingsButton, 308, 214);

    //labels voor bij de knoppen (homescreen)
    lv_obj_t* navLabel = lv_label_create(homeScreenTiles);
    lv_label_set_text(navLabel, "Navigation");
    lv_obj_set_pos(navLabel, 396, 30);
    lv_obj_t* optionsLabel = lv_label_create(homeScreenTiles);
    lv_label_set_text(optionsLabel, "Options");
    lv_obj_set_pos(optionsLabel, 396, 140);
    lv_obj_t* settingsLabel = lv_label_create(homeScreenTiles);
    lv_label_set_text(settingsLabel, "Settings");
    lv_obj_set_pos(settingsLabel, 396, 222);
    

    //Home buttons events
    lv_obj_add_event_cb(navigationButton, navBtnEvent, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(optionsButton, optionsBtnEvent, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(settingsButton, settingsBtnEvent, LV_EVENT_CLICKED, NULL);


    //Settings Tile inhoud
    lv_obj_t* settingTitle = lv_label_create(settingTile);
    lv_label_set_text(settingTitle, "Settings");
    lv_obj_set_pos(settingTitle, 32, 25);

    nightDayButton = lv_btn_create(settingTile);
    lv_obj_set_size(nightDayButton, 96, 96);
    lv_obj_set_pos(nightDayButton, 32, 92);

    accountButton = lv_btn_create(settingTile);
    lv_obj_set_size(accountButton, 96, 96);
    lv_obj_set_pos(accountButton, 172, 92);

    bluetoothButton = lv_btn_create(settingTile);
    lv_obj_set_size(bluetoothButton, 96, 96);
    lv_obj_set_pos(bluetoothButton, 172, 262);

    moreSettingsButton = lv_btn_create(settingTile);
    lv_obj_set_size(moreSettingsButton, 96, 96);
    lv_obj_set_pos(moreSettingsButton, 32, 262);

    //Labels voor settings buttons
    lv_obj_t* nightDayLabel = lv_label_create(settingTile);
    lv_label_set_text(nightDayLabel, "Day/Night");
    lv_obj_set_pos(nightDayLabel,  40, 190);
    lv_obj_t* accountLabel = lv_label_create(settingTile);
    lv_label_set_text(accountLabel, "Account");
    lv_obj_set_pos(accountLabel,  210, 190);
    lv_obj_t* bluetoothLabel = lv_label_create(settingTile);
    lv_label_set_text(bluetoothLabel, "Bluetooth");
    lv_obj_set_pos(bluetoothLabel,  200, 360);
    lv_obj_t* moreSettingsLabel = lv_label_create(settingTile);
    lv_label_set_text(moreSettingsLabel, "More");
    lv_obj_set_pos(moreSettingsLabel,  60, 360);

    // Events voor settings buttons
    lv_obj_add_event_cb(nightDayButton, nightDayBtnEvent, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(accountButton, accountBtnEvent, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(bluetoothButton, bluetoothBtnEvent, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(moreSettingsButton, moreSettingsBtnEvent, LV_EVENT_CLICKED, NULL);
}

//Style activity tiles container
    // static lv_style_t activityTilesStyle;
    // lv_style_init(&activityTilesStyle);
    // lv_style_set_bg_color(&activityTilesStyle, lv_color_hex(0xFFFFFF));
    // lv_style_set_opa(&activityTilesStyle, LV_OPA_COVER);