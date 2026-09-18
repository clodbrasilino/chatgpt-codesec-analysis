#include <stdio.h>
#include <math.h>

typedef struct {
    double r;
    double g;
    double b;
} RGB;

typedef struct {
    double h;
    double s;
    double v;
} HSV;

HSV rgb_to_hsv(RGB rgb) {
    HSV hsv = {0.0, 0.0, 0.0};
    double min, max, delta;

    min = rgb.r < rgb.g ? rgb.r : rgb.g;
    min = min < rgb.b ? min : rgb.b;

    max = rgb.r > rgb.g ? rgb.r : rgb.g;
    max = max > rgb.b ? max : rgb.b;

    hsv.v = max;
    delta = max - min;

    if (delta < 0.00001) {
        hsv.s = 0;
        hsv.h = 0;
        return hsv;
    }

    if (max > 0.0) {
        hsv.s = (delta / max);
    } else {
        hsv.s = 0.0;
        hsv.h = NAN;
        return hsv;
    }

    if (rgb.r >= max) {
        hsv.h = (rgb.g - rgb.b) / delta;
    } else if (rgb.g >= max) {
        hsv.h = 2.0 + (rgb.b - rgb.r) / delta;
    } else {
        hsv.h = 4.0 + (rgb.r - rgb.g) / delta;
    }

    hsv.h *= 60.0;

    if (hsv.h < 0.0) {
        hsv.h += 360.0;
    }

    return hsv;
}

int main(void) {
    RGB rgb = {0.5, 0.2, 0.8};
    HSV hsv = rgb_to_hsv(rgb);

    printf("RGB: (%.2f, %.2f, %.2f)\n", rgb.r, rgb.g, rgb.b);
    printf("HSV: (%.2f, %.2f, %.2f)\n", hsv.h, hsv.s, hsv.v);

    return 0;
}