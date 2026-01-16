#ifndef TRI_H
#define TRI_H

#include <iostream>
#include "color.h"

/* Bounding Box */
typedef struct {
   float minX, minY;
   float maxX, maxY;
} BBox;

/* triangle */
class tri {
  public:
	tri(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, color inC1, color inC2, color inC3) :  
		v0{x1, y1, z1}, v1{x2, y2, z2}, v2{x3, y3, z3}, c0(inC1), c1(inC2), c2(inC3) {}

	tri() : v0{0,0,0}, v1{0,0,0}, v2{0,0,0} {}

	color getInC1() const {return c1; }

	void computeBBox();

  public:
	double v0[3];
	double v1[3];
	double v2[3];
	color c0, c1, c2;
	BBox myBBox;
};

void tri::computeBBox() {

	myBBox.minX = v0[0];
	myBBox.minY = v0[1];
	myBBox.maxX = v0[0];
	myBBox.maxY = v0[1];
	if (v1[0] < myBBox.minX) myBBox.minX = v1[0];
	if (v2[0] < myBBox.minX) myBBox.minX = v2[0];

	if (v1[1] < myBBox.minY) myBBox.minY = v1[1];
	if (v2[1] < myBBox.minY) myBBox.minY = v2[1];

	if (v1[0] > myBBox.maxX) myBBox.maxX = v1[0];
	if (v2[0] > myBBox.maxX) myBBox.maxX = v2[0];

	if (v1[1] > myBBox.maxY) myBBox.maxY = v1[1];
	if (v2[1] > myBBox.maxY) myBBox.maxY = v2[1];

}

#endif