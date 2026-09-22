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
    
    if (rgb.r < 0.0 || rgb.r > 255.0 || rgb.g < 0.0 || rgb.g > 255.0 || rgb.b < 0.0 || rgb.b > 255.0) {
        return hsv;
    }

    double r = rgb.r / 255.0;
    double g = rgb.g / 255.0;
    double b = rgb.b / 255.0;

    double max = r;
    if (g > max) max = g;
    if (b > max) max = b;

    double min = r;
    if (g < min) min = g;
    if (b < min) min = b;

    double delta = max - min;

    hsv.v = max;

    if (max > 0.0) {
        hsv.s = delta / max;
    } else {
        hsv.s = 0.0;
        hsv.h = 0.0;
        return hsv;
    }

    if (delta > 0.0) {
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
    } else {
        hsv.h = 0.0;
    }

    return hsv;
}

int main(void) {
    RGB rgb1 = {255.0, 0.0, 0.0};
    HSV hsv1 = rgb_to_hsv(rgb1);
    printf("RGB(%.1f, %.1f, %.1f) -> HSV(%.1f, %.3f, %.3f)\n", rgb1.r, rgb1.g, rgb1.b, hsv1.h, hsv1.s, hsv1.v);

    RGB rgb2 = {0.0, 255.0, 0.0};
    HSV hsv2 = rgb_to_hsv(rgb2);
    printf("RGB(%.1f, %.1f, %.1f) -> HSV(%.1f, %.3f, %.3f)\n", rgb2.r, rgb2.g, rgb2.b, hsv2.h, hsv2.s, hsv2.v);

    RGB rgb3 = {128.0, 12.0, 240.0};
    HSV hsv3 = rgb_to_hsv(rgb3);
    printf("RGB(%.1f, %.1f, %.1f) -> HSV(%.1f, %.3f, %.3f)\n", rgb3.r, rgb3.g, rgb3.b, hsv3.h, hsv3.s, hsv3.v);

    RGB rgb_inv = {300.0, -10.0, 0.0};
    HSV hsv_inv = rgb_to_hsv(rgb_inv);
    printf("RGB(%.1f, %.1f, %.1f) -> HSV(%.1f, %.3f, %.3f)\n", rgb_inv.r, rgb_inv.g, rgb_inv.b, hsv_inv.h, hsv_inv.s, hsv_inv.v);

    return 0;
}