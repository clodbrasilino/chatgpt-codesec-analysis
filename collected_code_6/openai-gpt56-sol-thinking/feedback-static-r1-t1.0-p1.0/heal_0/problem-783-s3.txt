#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGBColor;

typedef struct {
    double hue;
    double saturation;
    double value;
} HSVColor;

bool rgb_to_hsv(const RGBColor *rgb, HSVColor *hsv)
{
    double red;
    double green;
    double blue;
    double maximum;
    double minimum;
    double delta;
    double hue;

    if (rgb == NULL || hsv == NULL) {
        return false;
    }

    red = (double)rgb->red / 255.0;
    green = (double)rgb->green / 255.0;
    blue = (double)rgb->blue / 255.0;

    maximum = red;
    if (green > maximum) {
        maximum = green;
    }
    if (blue > maximum) {
        maximum = blue;
    }

    minimum = red;
    if (green < minimum) {
        minimum = green;
    }
    if (blue < minimum) {
        minimum = blue;
    }

    delta = maximum - minimum;
    hue = 0.0;

    if (delta > 0.0) {
        if (maximum == red) {
            hue = 60.0 * ((green - blue) / delta);
        } else if (maximum == green) {
            hue = 60.0 * (((blue - red) / delta) + 2.0);
        } else {
            hue = 60.0 * (((red - green) / delta) + 4.0);
        }

        if (hue < 0.0) {
            hue += 360.0;
        }
    }

    hsv->hue = hue;
    hsv->saturation = maximum > 0.0 ? (delta / maximum) * 100.0 : 0.0;
    hsv->value = maximum * 100.0;

    return true;
}

int main(void)
{
    const RGBColor rgb = {255U, 99U, 71U};
    HSVColor hsv = {0.0, 0.0, 0.0};

    if (!rgb_to_hsv(&rgb, &hsv)) {
        fputs("RGB to HSV conversion failed.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("RGB: (%u, %u, %u)\n",
           (unsigned int)rgb.red,
           (unsigned int)rgb.green,
           (unsigned int)rgb.blue);
    printf("HSV: (%.2f, %.2f%%, %.2f%%)\n",
           hsv.hue,
           hsv.saturation,
           hsv.value);

    return EXIT_SUCCESS;
}