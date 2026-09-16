#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RgbColor;

typedef struct {
    double h;
    double s;
    double v;
} HsvColor;

bool rgb_to_hsv(const RgbColor *rgb, HsvColor *hsv) {
    if (rgb == NULL || hsv == NULL) {
        return false;
    }

    double r = (double)rgb->r / 255.0;
    double g = (double)rgb->g / 255.0;
    double b = (double)rgb->b / 255.0;

    double cmax = fmax(r, fmax(g, b));
    double cmin = fmin(r, fmin(g, b));
    double delta = cmax - cmin;

    hsv->v = cmax;

    if (cmax == 0.0) {
        hsv->s = 0.0;
        hsv->h = 0.0;
    } else {
        hsv->s = delta / cmax;

        if (delta == 0.0) {
            hsv->h = 0.0;
        } else if (cmax == r) {
            hsv->h = 60.0 * fmod((g - b) / delta, 6.0);
        } else if (cmax == g) {
            hsv->h = 60.0 * ((b - r) / delta + 2.0);
        } else {
            hsv->h = 60.0 * ((r - g) / delta + 4.0);
        }
    }

    if (hsv->h < 0.0) {
        hsv->h += 360.0;
    }

    return true;
}

int main(void) {
    RgbColor rgb1 = {255, 0, 0};
    HsvColor hsv1;

    if (rgb_to_hsv(&rgb1, &hsv1)) {
        printf("RGB(%u, %u, %u) -> HSV(%.2f, %.2f, %.2f)\n", rgb1.r, rgb1.g, rgb1.b, hsv1.h, hsv1.s, hsv1.v);
    }

    RgbColor rgb2 = {0, 255, 0};
    HsvColor hsv2;

    if (rgb_to_hsv(&rgb2, &hsv2)) {
        printf("RGB(%u, %u, %u) -> HSV(%.2f, %.2f, %.2f)\n", rgb2.r, rgb2.g, rgb2.b, hsv2.h, hsv2.s, hsv2.v);
    }

    RgbColor rgb3 = {0, 0, 255};
    HsvColor hsv3;

    if (rgb_to_hsv(&rgb3, &hsv3)) {
        printf("RGB(%u, %u, %u) -> HSV(%.2f, %.2f, %.2f)\n", rgb3.r, rgb3.g, rgb3.b, hsv3.h, hsv3.s, hsv3.v);
    }

    RgbColor rgb4 = {128, 128, 128};
    HsvColor hsv4;

    if (rgb_to_hsv(&rgb4, &hsv4)) {
        printf("RGB(%u, %u, %u) -> HSV(%.2f, %.2f, %.2f)\n", rgb4.r, rgb4.g, rgb4.b, hsv4.h, hsv4.s, hsv4.v);
    }

    RgbColor rgb5 = {0, 0, 0};
    HsvColor hsv5;

    if (rgb_to_hsv(&rgb5, &hsv5)) {
        printf("RGB(%u, %u, %u) -> HSV(%.2f, %.2f, %.2f)\n", rgb5.r, rgb5.g, rgb5.b, hsv5.h, hsv5.s, hsv5.v);
    }

    return 0;
}