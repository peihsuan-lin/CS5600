#include <stdio.h>
#include <math.h>
#include "mpg2km.h"

const float mile2km = 1.609344;
const float gallon2litter = 3.78541178;

float mpg2kml(float mpg) {
    if (mpg <= 0) {
        printf("Input should be greater than 0\n");
        return -1;
    }
    return mpg * mile2km / gallon2litter;
}
float mpg2lphm(float mpg) {
    if (mpg <= 0) {
        printf("Input should be greater than 0\n");
        return -1;
    }
    return 100 / (mpg * mile2km / gallon2litter);
}
float lph2mpg(float lph) {
    if (lph <= 0) {
        printf("Input should be greater than 0\n");
        return -1;
    }
    return 100 / (lph / gallon2litter * mile2km);
}