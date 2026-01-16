#pragma once
#include "color.h"

class shapes
{
    public:
        shapes() : inC(0), zIndex(0) {}
        shapes(color C, int zIndex) : inC(C), zIndex(zIndex) {}
        
        virtual double eval(double x, double y) = 0;
        color getInC(){ return inC; }
        int getZIndex() { return zIndex; }

    protected: 
        void setZindex(int zIndex) { this->zIndex = zIndex; }
        void setInC(color C){ this->inC = C; }

    private:
        color inC;
        int zIndex;
};