/*
 * LinP.CS5600.LearnC.c / Program in C
 *
 * Peihsuan Lin / CS5600 / Northeastern University
 * Spring 2024 / Jan 21, 2024
 *
 */
#include <stdio.h>
#include "mpg2km.h"

int main()
{
    // test cases
    printf("mpg2kml(10): %.2f == 4.25 ?\n", mpg2kml(10));
    printf("mpg2kml(25): %.2f == 10.62 ?\n", mpg2kml(25));
    printf("mpg2lphm(10): %.2f == 23.52 ?\n", mpg2lphm(10));
    printf("mpg2lphm(25): %.2f == 9.41 ?\n", mpg2lphm(25));
    printf("lph2mpg(10): %.2f == 23.52 ?\n", lph2mpg(10));
    printf("lph2mpg(25): %.2f == 9.41 ?\n", lph2mpg(25));
    
    // test bad input
    printf("mpg2kml(0): %.2f == -1.00 ?\n", mpg2kml(0));
    printf("mpg2lphm(-1): %.2f == -1.00 ?\n", mpg2lphm(-1));
    printf("lph2mpg(iii): %.2f == -1.00 ?\n", lph2mpg(0));

    return 0;
}
