#pragma once
#include <iostream>
#include "color.h"
#include "vec2.h"
#include "shapes.h"

/* simple data representation of an implicit ellipse */
class ellipse : public shapes {
  public:
	ellipse(double cX, double cY, double r1, double r2, color C, int zIndex)
	{
		this->centers.setX(cX);
		this->centers.setY(cY);
		this->radii.setX(r1);
		this->radii.setY(r2);
		this->setInC(C);
		this->setZindex(zIndex);
	}

	ellipse(vec2 pos, vec2 r, color C, int zIndex) : 
		centers(pos),
		radii(r)
		{
			this->setInC(C);
			this->setZindex(zIndex);
		}

	double eval(double x, double y) {
		return (((centers.getX()-x)*(centers.getX()-x))/(radii.getX()*radii.getX()) + 
				((centers.getY()-y)*(centers.getY()-y))/(radii.getY()*radii.getY()) - 1.0f);
	}
  private:
	vec2 centers; //center point of ellipse
	vec2 radii; //radii of the ellipse
};