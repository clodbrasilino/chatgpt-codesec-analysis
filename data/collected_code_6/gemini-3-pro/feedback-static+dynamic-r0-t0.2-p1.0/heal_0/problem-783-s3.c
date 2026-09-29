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
    HSV hsv;
    double r = rgb.r / 255.0;
    double g = rgb.g / 255.0;
    double b = rgb.b / 255.0;

    double max = fmax(r, fmax(g, b));
    double min = fmin(r, fmin(g, b));
    double delta = max - min;

    hsv.v = max;

    if (max > 0.0) {
        hsv.s = delta / max;
    } else {
        hsv.s = 0.0;
        hsv.h = 0.0;
        return hsv;
    }

    if (delta == 0.0) {
        hsv.h = 0.0;
    } else {
        if (max == r) {
            hsv.h = (g - b) / delta;
        } else if (max == g) {
            hsv.h = 2.0 + (b - r) / delta;
        } else {
            hsv.h = 4.0 + (r - g) / delta;
        }

        hsv.h *= 60.0;

        if (hsv.h < 0.0) {
            hsv.h += 360.0;
        }
    }

    return hsv;
}

int main(void) {
    RGB rgb = {255.0, 0.0, 0.0};
    HSV hsv = rgb_to_hsv(rgb);

    printf("RGB: %.1f, %.1f, %.1f\n", rgb.r, rgb.g, rgb.b);
    printf("HSV: %.1f, %.1f, %.1f\n", hsv.h, hsv.s, hsv.v);

    return 0;
}