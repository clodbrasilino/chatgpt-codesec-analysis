#include <stdio.h>
#include <math.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct {
    double h;
    double s;
    double v;
} HsvColor;

static int rgb_to_hsv(const RgbColor *rgb, HsvColor *hsv)
{
    double r;
    double g;
    double b;
    double max;
    double min;
    double delta;

    if (rgb == NULL || hsv == NULL) {
        return -1;
    }

    r = (double)rgb->r / 255.0;
    g = (double)rgb->g / 255.0;
    b = (double)rgb->b / 255.0;

    max = fmax(r, fmax(g, b));
    min = fmin(r, fmin(g, b));
    delta = max - min;

    hsv->v = max;

    if (max > 0.0) {
        hsv->s = delta / max;
    } else {
        hsv->s = 0.0;
    }

    if (delta > 0.0) {
        if (max == r) {
            hsv->h = 60.0 * fmod((g - b) / delta, 6.0);
        } else if (max == g) {
            hsv->h = 60.0 * (((b - r) / delta) + 2.0);
        } else {
            hsv->h = 60.0 * (((r - g) / delta) + 4.0);
        }

        if (hsv->h < 0.0) {
            hsv->h += 360.0;
        }
    } else {
        hsv->h = 0.0;
    }

    return 0;
}

int main(void)
{
    RgbColor rgb = { 255, 128, 0 };
    HsvColor hsv = { 0.0, 0.0, 0.0 };

    if (rgb_to_hsv(&rgb, &hsv) != 0) {
        fprintf(stderr, "Error: rgb_to_hsv failed\n");
        return 1;
    }

    printf("RGB: (%u, %u, %u)\n",
           (unsigned int)rgb.r,
           (unsigned int)rgb.g,
           (unsigned int)rgb.b);
    printf("HSV: (%.2f, %.4f, %.4f)\n", hsv.h, hsv.s, hsv.v);

    return 0;
}