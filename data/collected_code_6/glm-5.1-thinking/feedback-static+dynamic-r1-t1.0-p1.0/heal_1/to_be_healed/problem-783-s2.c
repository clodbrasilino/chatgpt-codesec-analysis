#include <stdio.h>
#include <math.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct {
    double h;
    double s;
    double v;
} HSV;

int rgb_to_hsv(const RGB *rgb, HSV *hsv) {
    if (rgb == NULL || hsv == NULL) {
        return -1;
    }

    double r = (double)rgb->r / 255.0;
    double g = (double)rgb->g / 255.0;
    double b = (double)rgb->b / 255.0;

    double cmax = r;
    if (g > cmax) cmax = g;
    if (b > cmax) cmax = b;

    double cmin = r;
    if (g < cmin) cmin = g;
    if (b < cmin) cmin = b;

    double delta = cmax - cmin;

    hsv->v = cmax;

    if (cmax == 0.0) {
        hsv->s = 0.0;
        hsv->h = 0.0;
        return 0;
    }

    hsv->s = delta / cmax;

    if (delta == 0.0) {
        hsv->h = 0.0;
        return 0;
    }

    if (cmax == r) {
        hsv->h = 60.0 * fmod(((g - b) / delta), 6.0);
    } else if (cmax == g) {
        hsv->h = 60.0 * (((b - r) / delta) + 2.0);
    } else {
        hsv->h = 60.0 * (((r - g) / delta) + 4.0);
    }

    if (hsv->h < 0.0) {
        hsv->h += 360.0;
    }

    return 0;
}

int main(void) {
    RGB color1 = {255, 0, 0};
    HSV hsv1;
    if (rgb_to_hsv(&color1, &hsv1) == 0) {
        printf("RGB(255, 0, 0) -> HSV(%f, %f, %f)\n", hsv1.h, hsv1.s, hsv1.v);
    }

    RGB color2 = {0, 255, 0};
    HSV hsv2;
    if (rgb_to_hsv(&color2, &hsv2) == 0) {
        printf("RGB(0, 255, 0) -> HSV(%f, %f, %f)\n", hsv2.h, hsv2.s, hsv2.v);
    }

    RGB color3 = {0, 0, 0};
    HSV hsv3;
    if (rgb_to_hsv(&color3, &hsv3) == 0) {
        printf("RGB(0, 0, 0) -> HSV(%f, %f, %f)\n", hsv3.h, hsv3.s, hsv3.v);
    }

    /* Possible weaknesses found:
     *  Condition 'rgb_to_hsv(NULL,NULL)!=0' is always true [knownConditionTrueFalse]
     *  Calling function 'rgb_to_hsv' returns -1
     *  Condition 'rgb_to_hsv(NULL,NULL)!=0' is always true
     */
    if (rgb_to_hsv(NULL, NULL) != 0) {
        printf("NULL pointer handled correctly.\n");
    }

    return 0;
}