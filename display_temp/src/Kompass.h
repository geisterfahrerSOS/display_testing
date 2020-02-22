#ifndef Kompass_h
#define Kompass_h

#include <Arduino.h>


class Winkel 
{
    
    public:
        Winkel();
        void startup();
        float winkel();
        float calc(float mag);
        uint16_t read12bit(byte regh, byte regl);
        void chipWrite(uint8_t reg, uint8_t data);
        byte chipRead(uint8_t reg);
    private:
    uint8_t _addr;
};
 
#endif