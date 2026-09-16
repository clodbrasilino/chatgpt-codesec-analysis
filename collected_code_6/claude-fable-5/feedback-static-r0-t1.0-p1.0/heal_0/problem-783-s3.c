#include <stdio.h>
#include <stdlib.h>

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

HSV rgb_to_hsv(RGB rgb)
{
    HSV hsv;
    double r = (double)rgb.r / 255.0;
    double g = (double)rgb.g / 255.0;
    double b = (double)rgb.b / 255.0;

    double max = r;
    if (g > max) {
        max = g;
    }
    if (b > max) {
        max = b;
    }

    double min = r;
    if (g < min) {
        min = g;
    }
    if (b < min) {
        min = b;
    }

    double delta = max - min;

    hsv.v = max;

    if (max > 0.0) {
        hsv.s = delta / max;
    } else {
        hsv.s = 0.0;
        hsv.h = 0.0;
        return hsv;
    }

    if (delta <= 0.0) {
        hsv.h = 0.0;
        return hsv;
    }

    if (max == r) {
        hsv.h = 60.0 * ((g - b) / delta);
    } else if (max == g) {
        hsv.h = 60.0 * (2.0 + (b - r) / delta);
    } else {
        hsv.h = 60.0 * (4.0 + (r - g) / delta);
    }

    if (hsv.h < 0.0) {
        hsv.h += 360.0;
    }

    return hsv;
}

int main(void)
{
    RGB test_colors[] = {
        {255u, 0u, 0u},
        {0u, 255u, 0u},
        {0u, 0u, 255u},
        {255u, 255u, 255u},
        {0u, 0u, 0u},
        {128u, 64u, 32u}
    };

    size_t count = sizeof(test_colors) / sizeof(test_colors[0]);
    size_t i;

    for (i = 0u; i < count; i++) {
        HSV hsv = rgb_to_hsv(test_colors[i]);
        if (printf("RGB(%u, %u, %u) -> HSV(%.2f, %.2f, %.2f)\n",
                   (unsigned int)test_colors[i].r,
                   (unsigned int)test_colors[i].g,
                   (unsigned int)test_colors[i].b,
                   hsv.h, hsv.s, hsv.v) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}