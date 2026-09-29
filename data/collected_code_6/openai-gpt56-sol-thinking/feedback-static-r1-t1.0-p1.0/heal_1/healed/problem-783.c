#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RgbColor;

typedef struct {
    double hue;
    double saturation;
    double value;
} HsvColor;

bool rgb_to_hsv(const RgbColor *rgb, HsvColor *hsv)
{
    double red;
    double green;
    double blue;
    double maximum;
    double minimum;
    double delta;

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

    hsv->value = maximum;
    hsv->saturation = maximum == 0.0 ? 0.0 : delta / maximum;

    if (delta == 0.0) {
        hsv->hue = 0.0;
    } else if (maximum == red) {
        hsv->hue = 60.0 * ((green - blue) / delta);
        if (hsv->hue < 0.0) {
            hsv->hue += 360.0;
        }
    } else if (maximum == green) {
        hsv->hue = 60.0 * (((blue - red) / delta) + 2.0);
    } else {
        hsv->hue = 60.0 * (((red - green) / delta) + 4.0);
    }

    return true;
}

static bool parse_rgb_component(const char *text, uint8_t *component)
{
    char *end;
    unsigned long value;

    if (text == NULL || component == NULL || text[0] == '-') {
        return false;
    }

    errno = 0;
    value = strtoul(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value > UINT8_MAX) {
        return false;
    }

    *component = (uint8_t)value;
    return true;
}

int main(int argc, char *argv[const])
{
    RgbColor rgb;
    HsvColor hsv;
    const char *const program_name =
        argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 4) {
        if (fprintf(stderr, "Usage: %s <red> <green> <blue>\n",
                    program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!parse_rgb_component(argv[1], &rgb.red) ||
        !parse_rgb_component(argv[2], &rgb.green) ||
        !parse_rgb_component(argv[3], &rgb.blue)) {
        if (fprintf(stderr,
                    "RGB components must be integers from 0 to 255.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!rgb_to_hsv(&rgb, &hsv)) {
        if (fprintf(stderr, "RGB to HSV conversion failed.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("H: %.2f S: %.4f V: %.4f\n",
               hsv.hue, hsv.saturation, hsv.value) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}