#pragma once

#include "LCD_esp32s3.h"  

class LCD_GFX : public LCD_esp32s3 {  
    public:
        LCD_GFX(LCD_esp32s3& vga);    
        ~LCD_GFX();           
        
        int getCol(int r, int g, int b);

        void cls(uint16_t col);
        void clsViewport(uint16_t col);
        void putPixel(int x, int y, uint16_t col);
        void hLine(int x1, int y, int x2, uint16_t col);
        void vLine(int x, int y1, int y2, uint16_t col);
        void rect(int x1, int y1, int x2, int y2, uint16_t col);
        void fillRect(int x1, int y1, int x2, int y2, uint16_t col);

    protected:
        LCD_esp32s3& _vga;  // ссылка, а не копия
};    

/*
        Black        = Col16<0,   0,   0>(),       // 0
        Blue         = Col16<0,   0,   170>(),     // 1
        Green        = Col16<0,   170, 0>(),       // 2
        Cyan         = Col16<0,   170, 170>(),     // 3
        Red          = Col16<170, 0,   0>(),       // 4
        Magenta      = Col16<170, 0,   170>(),     // 5
        Brown        = Col16<170, 85,  0>(),       // 6
        LightGray    = Col16<170, 170, 170>(),     // 7
        DarkGray     = Col16<85,  85,  85>(),      // 8
        LightBlue    = Col16<85,  85,  255>(),     // 9
        LightGreen   = Col16<85,  255, 85>(),      // 10
        LightCyan    = Col16<85,  255, 255>(),     // 11
        LightRed     = Col16<255, 85,  85>(),      // 12
        LightMagenta = Col16<255, 85,  255>(),     // 13
        Yellow       = Col16<255, 255, 85>(),      // 14
        White        = Col16<255, 255, 255>()      // 15
*/