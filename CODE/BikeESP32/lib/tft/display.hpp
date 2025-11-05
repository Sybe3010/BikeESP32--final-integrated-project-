#pragma once

#define LGFX_USE_V1

#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ILI9488   _panel_instance;
  lgfx::Light_PWM       _light_instance;
  lgfx::Touch_FT5x06    _touch_instance;
  
  public: 
  LGFX(void)
  {
    {                                        
      auto cfg = _panel_instance.config();

      cfg.pin_cs = -1;   
      cfg.pin_rst = -1;  
      cfg.pin_busy = -1; 

      cfg.memory_width = 320;   
      cfg.memory_height = 480;  
      cfg.panel_width = 320;    
      cfg.panel_height = 480;   
      cfg.offset_x = 0;         
      cfg.offset_y = 0;         
      cfg.offset_rotation = 0;  
      cfg.dummy_read_pixel = 8; 
      cfg.dummy_read_bits = 1;  
      cfg.readable = true;      
      cfg.invert = true;     
      cfg.rgb_order = false;    
      cfg.dlen_16bit = true;    
      cfg.bus_shared = true;    

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _light_instance.config();
      cfg.pin_bl = GPIO_NUM_10;
      cfg.invert = false;
      cfg.freq = 44100;
      cfg.pwm_channel = 7;

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);
    }

    {
      auto cfg = _touch_instance.config();

      cfg.x_min = 0;
      cfg.x_max = 319;
      cfg.y_min = 0;
      cfg.y_max = 479;
      cfg.pin_int = GPIO_NUM_30;
      cfg.bus_shared = true;
      cfg.offset_rotation = 0;

      cfg.i2c_port = 0;
      cfg.i2c_addr = 0x38;
      cfg.pin_sda = GPIO_NUM_38;
      cfg.pin_scl = GPIO_NUM_39;
      cfg.freq = 400000;

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }
    setPanel(&_panel_instance);
  }
};