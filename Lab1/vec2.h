#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <iostream>

#include "util.h"

using std::sqrt;

class vec2 {
	public:
		vec2() : x(0), y(0) {}
		vec2(int x, int y) : x(x), y(y) {}

		void setX(int x)
		{
			this->x = x;
		}

		void setY(int y)
		{
			this->y = y;
		}

		int getX()
		{
			return this->x;
		}

		int getY()
		{
			return this->y;
		}

		vec2& operator+=(vec2 &v) {
			this->x = x + v.getX();
			this->y = y + v.getY();
			return *this;
		}

		vec2& operator*=(const double Sc) {
			this->x = x * Sc;
			this->y = y * Sc;
			return *this;
		}

	private:
		int x;
		int y;
};

// inline std::ostream& operator<<(std::ostream &out, const vec2 &v) {
// 	//fill in if desired 
// 	//incomplete
// 	//return out << 
// }


#endif
