//
// Created by m2-bukovics on 17/11/2022.
//

#include "Vector.h"
#include <cmath>

void Vector::normalise() {

 float mag = std::sqrt((x * x) + (y * y));
 x = x / mag;
 y = y /mag;

}
