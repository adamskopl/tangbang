/* 
   This file is part of Tangbang.

   Tangbang is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Tangbang is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Tangbang.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

typedef float scalar_t;  // skalar


class vector2d
{
public:
     scalar_t x;
     scalar_t y;

public:

     vector2d(scalar_t a = 0, scalar_t b = 0, scalar_t c = 0) : x(a), y(b){}
     vector2d(const vector2d &vec) : x(vec.x), y(vec.y) {}

     const vector2d &operator=(const vector2d &vec)
     {
          x = vec.x;
          y = vec.y;

          return *this;
     }

     const bool operator==(const vector2d &vec) const
     {
          return ((x == vec.x) && (y == vec.y));
     }

     const bool operator!=(const vector2d &vec) const
     {
          return !(*this == vec);
     }

     const vector2d operator+(const vector2d &vec) const
     {
          return vector2d(x + vec.x, y + vec.y);
     }

     const vector2d operator+() const
     {    
          return vector2d(*this);
     }

     const vector2d& operator+=(const vector2d& vec)
     {    x += vec.x;
          y += vec.y;
          return *this;
     }

     const vector2d operator-(const vector2d& vec) const
     {    
          return vector2d(x - vec.x, y - vec.y);
     }
     
     const vector2d operator-() const
     {    
          return vector2d(-x, -y);
     }

     const vector2d &operator-=(const vector2d& vec)
     {
          x -= vec.x;
          y -= vec.y;

          return *this;
     }

     const vector2d &operator*=(const scalar_t &s)
     {
          x *= s;
          y *= s;
          
          return *this;
     }

     const vector2d &operator/=(const scalar_t &s)
     {
          const float recip = 1/s; // dla efektywno彡i

          x *= recip;
          y *= recip;

          return *this;
     }

     const vector2d operator*(const scalar_t &s) const
     {
          return vector2d(x*s, y*s);
     }

     friend inline const vector2d operator*(const scalar_t &s, const vector2d &vec)
     {
          return vec*s;
     }

/*   friend inline const vector2d operator*(const vector2d &vec, const scalar_t &s)
     {
          return vector2d(vec.x*s, vec.y*s, vec.z*s);
     }

*/   // dzielenie wektora przez skalar
     const vector2d operator/(scalar_t s) const
     {
       s = 1/s;

       return vector2d(s*x, s*y);
     }
     

     const scalar_t DotProduct(const vector2d &vec) const
     {
          return x*vec.x + y*vec.x;
     }

     
     const scalar_t operator%(const vector2d &vec) const
     {
          return x*vec.x + y*vec.x;
     }


     const scalar_t Length() const
     {
          return (scalar_t)sqrt((double)(x*x + y*y));
     }

     const vector2d UnitVector() const
     {
          return (*this) / Length();
     }

     void Normalize()
     {
          (*this) /= Length();
     }

     const scalar_t operator!() const
     {
          return sqrtf(x*x + y*y);
     }

     const vector2d operator | (const scalar_t length) const
     {
          return *this * (length / !(*this));
     }

     const vector2d& operator |= (const float length)
     {
          return *this = *this | length;
     }

     const float inline Angle(const vector2d& normal) const
     {
          return acosf(*this % normal);
     }

     const vector2d inline Reflection(const vector2d& normal) const
     {    
          const vector2d vec(*this | 1);     // normalizuje wektor
          return (vec - normal * 2.0 * (vec % normal)) * !*this;
     }

};

#endif
