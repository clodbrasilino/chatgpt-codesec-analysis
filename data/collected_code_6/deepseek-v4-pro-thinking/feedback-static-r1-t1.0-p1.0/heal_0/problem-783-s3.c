#include <stdint.h>
#include <stdio.h>
#include <math.h>

int rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b, double *h, double *s, double *v) {
    if (h == NULL || s == NULL || v == NULL) {
        return -1;
    }

    double rn = r / 255.0;
    double gn = g / 255.0;
    double bn = b / 255.0;

    double max = fmax(rn, fmax(gn, bn));
    double min = fmin(rn, fmin(gn, bn));
    double delta = max - min;

    *v = max;

    if (max == 0.0) {
        *h = 0.0;
        *s = 0.0;
        return 0;
    }

    *s = delta / max;

    if (delta == 0.0) {
        *h = 0.0;
        return 0;
    }

    if (max == rn) {
        *h = 60.0 * ((gn - bn) / delta);
    } else if (max == gn) {
        *h = 60.0 * (((bn - rn) / delta) + 2.0);
    } else {
        *h = 60.0 * (((rn - gn) / delta) + 4.0);
    }

    if (*h < 0.0) {
        *h += 360.0;
    }

    return 0;
}

int main(void) {
    uint8_t r = 255;
    uint8_t g = 0;
    uint8_t b = 0;
    double h;
    double s;
    double v;

    if (rgb_to_hsv(r, g, b, &h, &s, &v) != 0) {
        return 1;
    }

    printf("RGB(%u, %u, %u) -> HSV(%.2f, %.2f, %.2f)\n",
           (unsigned int)r, (unsigned int)g, (unsigned int)b, h, s, v);

    return 0;
}