#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

typedef struct {
    double h;
    double s;
    double v;
} HSV;

int rgb_to_hsv(unsigned char r, unsigned char g, unsigned char b, HSV *hsv)
{
    double rd, gd, bd;
    double max, min, delta;

    if (hsv == NULL) {
        return -1;
    }

    rd = (double)r / 255.0;
    gd = (double)g / 255.0;
    bd = (double)b / 255.0;

    max = rd;
    if (gd > max) {
        max = gd;
    }
    if (bd > max) {
        max = bd;
    }

    min = rd;
    if (gd < min) {
        min = gd;
    }
    if (bd < min) {
        min = bd;
    }

    delta = max - min;

    hsv->v = max;

    if (max > 0.0) {
        hsv->s = delta / max;
    } else {
        hsv->s = 0.0;
    }

    if (delta <= 0.0) {
        hsv->h = 0.0;
    } else if (r >= g && r >= b) {
        hsv->h = 60.0 * fmod((gd - bd) / delta, 6.0);
        if (hsv->h < 0.0) {
            hsv->h += 360.0;
        }
    } else if (g >= b) {
        hsv->h = 60.0 * (((bd - rd) / delta) + 2.0);
    } else {
        hsv->h = 60.0 * (((rd - gd) / delta) + 4.0);
    }

    return 0;
}

static int parse_channel(const char *str, unsigned char *out)
{
    char *end = NULL;
    long value;

    if (str == NULL || out == NULL) {
        return -1;
    }

    errno = 0;
    value = strtol(str, &end, 10);

    if (errno != 0 || end == str || *end != '\0' || value < 0 || value > 255) {
        return -1;
    }

    *out = (unsigned char)value;
    return 0;
}

int main(int argc, char *argv[])
{
    unsigned char r = 255;
    unsigned char g = 128;
    unsigned char b = 0;
    HSV hsv;

    if (argc == 4) {
        if (parse_channel(argv[1], &r) != 0 ||
            parse_channel(argv[2], &g) != 0 ||
            parse_channel(argv[3], &b) != 0) {
            fprintf(stderr, "Invalid RGB values. Use integers in range 0-255.\n");
            return EXIT_FAILURE;
        }
    } else if (argc != 1) {
        fprintf(stderr, "Usage: %s [r g b]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (rgb_to_hsv(r, g, b, &hsv) != 0) {
        fprintf(stderr, "RGB to HSV conversion failed.\n");
        return EXIT_FAILURE;
    }

    printf("RGB(%u, %u, %u) -> HSV(%.2f, %.4f, %.4f)\n",
           (unsigned int)r, (unsigned int)g, (unsigned int)b,
           hsv.h, hsv.s, hsv.v);

    return EXIT_SUCCESS;
}