#include "Math.h"
#include "esp_random.h"        // esp_random, esp_fill_random
#include "bootloader_random.h" // bootloader_random_enable, disable
/*
// одно 32-битное случайное число
uint32_t Math::randomU32() {
    return esp_random();
}

// случайное число в диапазоне [min, max]
int Math::randomInt(int min, int max) {
    if (min >= max) return min;
    uint32_t val = randomU32();
    return min + (val % (max - min + 1));
}

// случайное float в диапазоне [0, 1)
float Math::randomFloat() {
    return (float)randomU32() / (float)UINT32_MAX;
}

// случайное double в диапазоне [0, 1)
double Math::randomDouble() {
    return (double)randomU32() / (double)UINT32_MAX;
}

// случайное bool (true/false)
bool Math::randomBool() {
    return (randomU32() & 1) != 0;
}

// случайное float в диапазоне [min, max)
float Math::randomRangeFloat(float min, float max) {
    return min + (randomFloat() * (max - min));
}

// заполнение буфера случайными байтами
void Math::randomBytes(void* buf, size_t len) {
    esp_fill_random(buf, len);
}

// включить "истинный" TRNG (SAR ADC источник энтропии)
//При включении enableTrueRandom() — подключается SAR ADC шум, и получаем «настоящие» случайные числа (рекомендовано для безопасности и криптографии).
void Math::enableTrueRandom() {
    bootloader_random_enable();
}

// выключить TRNG (освободить SAR ADC для Wi-Fi/BT/ADC)
//По умолчанию работает встроенный генератор с осциллятором (хорош для игр, графики, спрайтов).
void Math::disableTrueRandom() {
    bootloader_random_disable();
}
*/