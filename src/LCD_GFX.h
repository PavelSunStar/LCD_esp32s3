#pragma once

#include "LCD_esp32s3.h"  

class LCD_GFX : public LCD_esp32s3 {  
    public:
        LCD_GFX(LCD_esp32s3& vga);    
        ~LCD_GFX();           
        
        void cls(uint16_t col);
        //void clsViewport(uint16_t col);
        //void putPixel(int x, int y, uint16_t col);
        //void hLine(int x1, int y, int x2, uint16_t col);
        //void vLine(int x, int y1, int y2, uint16_t col);
        //void rect(int x1, int y1, int x2, int y2, uint16_t col);
        void fillRect(int x1, int y1, int x2, int y2, uint16_t col);

    protected:
        LCD_esp32s3& _vga;  // ссылка, а не копия
};    