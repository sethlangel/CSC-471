#pragma once

#include "vec2.h"
#include "color.h"
#include "shapes.h"

class rect : public shapes{
    public:
        rect() : 
            topLeft(), 
            bottomRight() {}
        rect(vec2 topLeft, vec2 bottomRight, color C, int zIndex) : 
            topLeft(topLeft), 
            bottomRight(bottomRight)
            {
                this->setInC(C);
                this->setZindex(zIndex);
            }

        double eval(double x, double y)
        {
            int minX = topLeft.getX();
            int maxX = bottomRight.getX();
            int minY = bottomRight.getY();
            int maxY = topLeft.getY();

            if(minX < x && x < maxX && minY < y && y < maxY){
                return -1;
            }

            return 0;
        }
        
    private:   
        vec2 topLeft, bottomRight;
};