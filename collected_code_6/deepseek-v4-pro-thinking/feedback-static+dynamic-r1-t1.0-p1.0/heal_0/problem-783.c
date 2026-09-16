#include <stdio.h>

typedef struct {
    int r;
    int g;
    int b;
} RGB;

typedef struct {
    float h;
    float s;
    float v;
} HSV;

int rgb_to_hsv(const RGB *rgb, HSV *hsv) {
    if (rgb == NULL || hsv == NULL) {
        return -1;
    }

    if (rgb->r < 0 || rgb->r > 255 ||
        rgb->g < 0 || rgb->g > 255 ||
        rgb->b < 0 || rgb->b > 255) {
        return -2;
    }

    float r = rgb->r / 255.0f;
    float g = rgb->g / 255.0f;
    float b = rgb->b / 255.0f;

    float max = r;
    if (g > max) {
        max = g;
    }
    if (b > max) {
        max = b;
    }

    float min = r;
    if (g < min) {
        min = g;
    }
    if (b < min) {
        min = b;
    }

    float delta = max - min;

    hsv->v = max;

    if (max <= 0.0f) {
        hsv->h = 0.0f;
        hsv->s = 0.0f;
        return 0;
    }

    hsv->s = delta / max;

    if (delta <= 0.0f) {
        hsv->h = 0.0f;
    } else {
        float h;

        if (max == r) {
            h = (g - b) / delta;
            if (h < 0.0f) {
                h += 6.0f;
            }
        } else if (max == g) {
            h = (b - r) / delta + 2.0f;
        } else {
            h = (r - g) / delta + 4.0f;
        }

        h *= 60.0f;

        if (h < 0.0f) {
            h += 360.0f;
        }

        hsv->h = h;
    }

    return 0;
}

int main(void) {
    RGB rgb = {255, 0, 0};
    HSV hsv;

    int status = rgb_to_hsv(&rgb, &hsv);

    if (status != 0) {
        printf("Invalid input\n");
        return 1;
    }

    printf("H: %.2f S: %.2f V: %.2f\n", hsv.h, hsv.s, hsv.v);

    return 0;
}