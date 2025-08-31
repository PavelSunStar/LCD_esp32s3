#pragma once

#include "esp_async_memcpy.h"
#include <esp_lcd_panel_rgb.h>

//LCD connect pins ----------------------------------------------------------------------------------------------------
//R
#define VGA_PIN_NUM_DATA0          4
#define VGA_PIN_NUM_DATA1          5
#define VGA_PIN_NUM_DATA2          6
#define VGA_PIN_NUM_DATA3          7
#define VGA_PIN_NUM_DATA4          15

//G
#define VGA_PIN_NUM_DATA5          16
#define VGA_PIN_NUM_DATA6          17
#define VGA_PIN_NUM_DATA7          18
#define VGA_PIN_NUM_DATA8          8
#define VGA_PIN_NUM_DATA9          9
#define VGA_PIN_NUM_DATA10         14

//B
#define VGA_PIN_NUM_DATA11         10
#define VGA_PIN_NUM_DATA12         11
#define VGA_PIN_NUM_DATA13         12
#define VGA_PIN_NUM_DATA14         13
#define VGA_PIN_NUM_DATA15         21

/*
//R
#define VGA_PIN_NUM_DATA0          4
#define VGA_PIN_NUM_DATA1          5
#define VGA_PIN_NUM_DATA2          6
#define VGA_PIN_NUM_DATA3          7
#define VGA_PIN_NUM_DATA4          15

//G
#define VGA_PIN_NUM_DATA5          9
#define VGA_PIN_NUM_DATA6          10
#define VGA_PIN_NUM_DATA7          11
#define VGA_PIN_NUM_DATA8          12
#define VGA_PIN_NUM_DATA9          13
#define VGA_PIN_NUM_DATA10         14

//B
#define VGA_PIN_NUM_DATA11         16
#define VGA_PIN_NUM_DATA12         17
#define VGA_PIN_NUM_DATA13         18
#define VGA_PIN_NUM_DATA14         8
#define VGA_PIN_NUM_DATA15         3
*/

//Other
#define VGA_PIN_NUM_DISP_EN     -1
#define VGA_PIN_NUM_PCLK        -1
#define VGA_PIN_NUM_DE          -1
#define VGA_PIN_NUM_VSYNC       2
#define VGA_PIN_NUM_HSYNC       1

class LCD_esp32s3{
    public:
        //Pixel clock, hRes, VRes, ColBit, BPP
        //H back porch, H front porch, H pulse width,
        //V back porch, V front porch, V pulse width,
        //DivX, DivY

        static constexpr int MODE160x120x8[] = {25'000'000, 640, 480, 8, 8, 48, 16, 96, 33, 10, 2, 2, 30720};//10
        static constexpr int MODE320x240x8[] = {25'000'000, 640, 480, 8, 8, 48, 16, 96, 33, 10, 2, 1, 30720};
        static constexpr int MODE640x480x8[] = {25'000'000, 640, 480, 8, 8, 48, 16, 96, 33, 10, 2, 0, 30720};

        static constexpr int MODE200x150x8[] = {40'000'000, 800, 600, 8, 8, 88, 40, 128, 23, 1, 4, 2, 48000};//10
        static constexpr int MODE400x300x8[] = {40'000'000, 800, 600, 8, 8, 88, 40, 128, 23, 1, 4, 1, 48000};
        static constexpr int MODE800x600x8[] = {40'000'000, 800, 600, 8, 8, 88, 40, 128, 23, 1, 4, 0, 48000};

        static constexpr int MODE256x192x8[] = {60'000'000, 1024, 768, 8, 8, 160, 24, 136, 29, 3, 6, 2, 49152};//16
        static constexpr int MODE512x384x8[] = {60'000'000, 1024, 768, 8, 8, 160, 24, 136, 29, 3, 6, 1, 65536};
        static constexpr int MODE1024x768x8[] = {60'000'000, 1024, 768, 8, 8, 160, 24, 136, 29, 3, 6, 0, 32768};
        
        uint8_t* _buf8 = nullptr;
		uint16_t* _buf16 = nullptr;
        uint32_t* _fastY = nullptr;
        int _frontBuff, _backBuff;
        bool _swap = false;
        bool _swapRequest = false;

        LCD_esp32s3();         // Конструктор 
        ~LCD_esp32s3();        // Деструктор

        int getWidth()      {return _width;};
        int getHeight()     {return _height;};
        int getXX()         {return _xx;};
        int getYY()         {return _yy;};
        int getColBit()     {return _colBit;};
        int getSize()       {return _size;};

        int getScrWidth()   {return _scrWidth;};
        int getScrHeight()  {return _scrHeight;};        
        int getScrXX()      {return _scrXX;};
        int getScrYY()      {return _scrYY;};
        int getBpp()        {return _bpp;};
        int getScale()      {return _scale;};
        int getScrSize()    {return _scrSize;};

        //Viewport
        int get_vX1()       {return _vX1;};
        int get_vX2()       {return _vX2;};
        int get_vY1()       {return _vY1;};
        int get_vY2()       {return _vY2;};
        int get_vWidth()    {return _vWidth;};
        int get_vHeight()   {return _vHeight;};
        
        bool init(const int *mode, bool dBuff = true, bool psRam = true);
        void printInfo();
        void setViewport(int x1, int y1, int x2, int y2);
        void swap();   

   protected:
        //Параметры режима
        int _pclk_hz;
        int _width, _height, _xx, _yy, _size;
        int _colBit, _bpp;
        int _hsync_back_porch;
        int _hsync_front_porch;
        int _hsync_pulse_width;
        int _vsync_back_porch;
        int _vsync_front_porch;
        int _vsync_pulse_width; 
        int _scale; 
        size_t _bounce_buffer_size_px, _lastBounceBufferPos;
        int _alignBuff;        
        bool _psRam, _dBuff;
        int _lines, _tik;
        int _width2X;

        //Screen
        int _scrWidth, _scrHeight;
        int _scrSize, _scrXX, _scrYY;
        
        //Viewport
        int _vX1, _vX2;
        int _vY1, _vY2;
        int _vWidth, _vHeight;

        esp_lcd_panel_handle_t _panel_handle = NULL;
        static bool IRAM_ATTR on_bounce_empty           (esp_lcd_panel_handle_t panel, void *bounce_buf, int pos_px, int len_bytes, void *user_ctx);
        static bool IRAM_ATTR on_color_trans_done       (esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx);
        static bool IRAM_ATTR on_vsync                  (esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx);
        static bool IRAM_ATTR on_bounce_frame_finish    (esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx);
        static bool IRAM_ATTR on_frame_buf_complete     (esp_lcd_panel_handle_t panel, const esp_lcd_rgb_panel_event_data_t *edata, void *user_ctx);

	    SemaphoreHandle_t _sem_vsync_end;
	    SemaphoreHandle_t _sem_gui_ready;

        bool setPanelConfig();
        void regCallbackSemaphore();  

    protected:

};    

//uint8_t *buffer = dmaBuffer->getBuffer8(backBuffer);
//r = min((rand() & 31) + r, 255);
//g = min((rand() & 31) + g, 255);
//b = min((rand() & 63) + b, 255);
//buffer[mode->hRes * v + h] = (r >> 5) | ((g >> 5) << 3) | ((b >>))
