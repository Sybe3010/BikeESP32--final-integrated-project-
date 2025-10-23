#pragma once

#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
  lgfx::Panel_ST7735S _panel_instance;
  lgfx::Bus_SPI _bus_instance; // SPI bus instance

public:
  LGFX(void)
  {
    { // Bus control settings
      auto cfg = _bus_instance.config();

      // SPI bus settings
      cfg.spi_mode = 0;          // SPI communication mode (0 ~ 3)
      cfg.freq_write = 16000000; // SPI clock for transmission (up to 80MHz)
      cfg.freq_read = 20000000;  // SPI clock for reception
      cfg.dma_channel = SPI_DMA_CH_AUTO; // Use automatic DMA channel assignment
      cfg.spi_3wire = false;
      cfg.pin_sclk = 13; // SCLK pin number
      cfg.pin_mosi = 14; // MOSI pin number
      cfg.pin_miso = -1; // MISO pin number (disable if not used)
      cfg.pin_dc = 10;   // D/C pin number
      
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    { // Display panel control settings
      auto cfg = _panel_instance.config();

      cfg.pin_cs = 9;           // CS pin number
      cfg.pin_rst = 21;          // RST pin number (disable if not used)
      cfg.pin_busy = -1;         // BUSY pin number (disable if not used)

      cfg.panel_width  = 128;
      cfg.panel_height = 160;
      cfg.offset_rotation = 0;
      cfg.readable = false;
      cfg.invert = false;
      cfg.rgb_order = false;
      cfg.bus_shared = false;
      
      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance); // Assign the panel to the display
  }
};
   