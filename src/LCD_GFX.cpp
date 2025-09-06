#include <Arduino.h>
#include "LCD_GFX.h"
#include <cstring>

LCD_GFX::LCD_GFX(LCD_esp32s3& vga) : _vga(vga){

}

LCD_GFX::~LCD_GFX(){

}

int LCD_GFX::getCol(int r, int g, int b) {
    if (_vga.getBpp() == 16) {
        // формируем 16-битный цвет RGB565
        return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);      
    } 
    else if (_vga.getBpp() == 8) {
        // формируем 8-битный цвет RGB332
        return ((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6); 
    }
    
    return 0;
}


        //return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
void LCD_GFX::cls(uint16_t col){
    if (_vga.getBpp() == 16){
        uint16_t* scr = _vga._buf16 + _vga._backBuff;
        
        memset(scr, col, _vga.getScrSize() << 1);
    } else {        
        uint8_t color = (uint8_t)(col & 0xFF); 
        uint8_t* scr = _vga._buf8 + _vga._backBuff;

        memset(scr, color, _vga.getScrSize());
    } 
}

void LCD_GFX::putPixel(int x, int y, uint16_t col) {
    if (x < _vga.get_vX1() || y < _vga.get_vY1() || x > _vga.get_vX2() ||  y > _vga.get_vY2()) return;

    if (_vga.getBpp() == 16){

    } else {
        uint8_t* scr = _vga._buf8 + _vga._backBuff;
        scr += _vga._fastY[y] + x;

        *scr = (uint8_t)col;
    }
}

void LCD_GFX::hLine(int x1, int y, int x2, uint16_t col){
    if (x1 > x2) std::swap(x1, x2);
    if (y < _vga.get_vY1() || y > _vga.get_vY2()) return;
    x1 = std::max(x1, _vga.get_vX1());
    x2 = std::min(x2, _vga.get_vX2());
    int size = x2 - x1 + 1;

    if (_vga.getBpp() == 16){

    } else {
        uint8_t* scr = _vga._buf8 + _vga._backBuff;
        scr += _vga._fastY[y] + x1;
        
        memset(scr, col, size);
    }                        
}

void LCD_GFX::vLine(int x, int y1, int y2, uint16_t col){
    if (x < _vga.get_vX1() || x > _vga.get_vX2()) return;
    if (y1 > y2) std::swap(y1, y2);
    if (y2 < _vga.get_vY1() || y1 > _vga.get_vY2()) return;

    y1 = std::max(y1, _vga.get_vY1());
    y2 = std::min(y2, _vga.get_vY2());
    int skip = _vga.getScrWidth();
    int size = y2 - y1 + 1;

    if (_vga.getBpp() == 16){
        uint16_t* scr = _vga._buf16 + _vga._backBuff;
        scr += _vga._fastY[y1] + x;

        while (size-- > 0){
            *scr = col;
            scr += skip; 
        }        
    } else {
        uint8_t* scr = _vga._buf8 + _vga._backBuff;
        scr += _vga._fastY[y1] + x;
        uint8_t color = (uint8_t)(col & 0xFF);

        while (size-- > 0){
            *scr = color;
            scr += skip; 
        }
    }   
}

void LCD_GFX::rect(int x1, int y1, int x2, int y2, uint16_t col){
    hLine(x1, y1, x2, col);
    vLine(x1, y1, y2, col);
    vLine(x2, y1, y2, col);
    hLine(x1, y2, x2, col);
}

void LCD_GFX::fillRect(int x1, int y1, int x2, int y2, uint16_t col){
    if (x1 > x2) std::swap(x1, x2); 
    if (y1 > y2) std::swap(y1, y2);
    if (x1 > _vga.get_vX2() || y1 > _vga.get_vY2() || x2 < _vga.get_vX1() || y2 < _vga.get_vY1()) return;

    x1 = std::max(x1, _vga.get_vX1());
    y1 = std::max(y1, _vga.get_vY1());
    x2 = std::min(x2, _vga.get_vX2());
    y2 = std::min(y2, _vga.get_vY2()); 
    
    int sizeX = x2 - x1 + 1;
    int sizeY = y2 - y1 + 1;
    int skip = _vga.getScrWidth();

    if (_vga.getBpp() == 16){

    } else {
        uint8_t* scr = _vga._buf8 + _vga._backBuff;
        scr += _vga._fastY[y1] + x1; 
        uint8_t color = (uint8_t)(col & 0xFF);
        
        while (sizeY-- > 0){
            memset(scr, color, sizeX); 
            scr += skip; 
        }        
    }
}

void LCD_GFX::clsViewport(uint16_t col){
    if (_vga.getBpp() == 16){

    } else {
        uint8_t* scr = _vga._buf8 + _vga._backBuff;
        scr += _vga._fastY[_vga.get_vY1()] + _vga.get_vX1();
        int sizeX = _vga.get_vWidth();
        int sizeY = _vga.get_vHeight();
        int skip = _vga.getScrWidth();
        uint8_t color = (uint8_t)(col & 0xFF);

        while (sizeY-- > 0){
            memset(scr, color, sizeX); 
            scr += skip; 
        }        
    }
}
