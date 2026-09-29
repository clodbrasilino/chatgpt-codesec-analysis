#include <stdio.h>

void rgb_to_hsv(float r, float g, float b, float *h, float *s, float *v) {
    if (h == NULL || s == NULL || v == NULL) {
        return;
    }

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

    *v = max;

    if (max == 0.0f) {
        *s = 0.0f;
    } else {
        *s = delta / max;
    }

    if (delta == 0.0f) {
        *h = 0.0f;
    } else if (max == r) {
        *h = 60.0f * ((g - b) / delta);
        if (*h < 0.0f) {
            *h += 360.0f;
        }
    } else if (max == g) {
        *h = 60.0f * (((b - r) / delta) + 2.0f);
    } else {
        *h = 60.0f * (((r - g) / delta) + 4.0f);
    }
}

int main(void) {
    float h, s, v;
    float r, g, b;

    r = 1.0f; g = 0.0f; b = 0.0f;
    rgb_to_hsv(r, g, b, &h, &s, &v);
    printf("RGB(%.2f, %.2f, %.2f) -> HSV(%.2f, %.2f, %.2f)\n", r, g, b, h, s, v);

    r = 0.0f; g = 1.0f; b = 0.0f;
    rgb_to_hsv(r, g, b, &h, &s, &v);
    printf("RGB(%.2f, %.2f, %.2f) -> HSV(%.2f, %.2f, %.2f)\n", r, g, b, h, s, v);

    r = 0.0f; g = 0.0f; b = 1.0f;
    rgb_to_hsv(r, g, b, &h, &s, &v);
    printf("RGB(%.2f, %.2f, %.2f) -> HSV(%.2f, %.2f, %.2f)\n", r, g, b, h, s, v);

    r = 1.0f; g = 1.0f; b = 1.0f;
    rgb_to_hsv(r, g, b, &h, &s, &v);
    printf("RGB(%.2f, %.2f, %.2f) -> HSV(%.2f, %.2f, %.2f)\n", r, g, b, h, s, v);

    r = 0.0f; g = 0.0f; b = 0.0f;
    rgb_to_hsv(r, g, b, &h, &s, &v);
    printf("RGB(%.2f, %.2f, %.2f) -> HSV(%.2f, %.2f, %.2f)\n", r, g, b, h, s, v);

    r = 0.5f; g = 0.5f; b = 0.5f;
    rgb_to_hsv(r, g, b, &h, &s, &v);
    printf("RGB(%.2f, %.2f, %.2f) -> HSV(%.2f, %.2f, %.2f)\n", r, g, b, h, s, v);

    r = 0.7f; g = 0.3f; b = 0.6f;
    rgb_to_hsv(r, g, b, &h, &s, &v);
    printf("RGB(%.2f, %.2f, %.2f) -> HSV(%.2f, %.2f, %.2f)\n", r, g, b, h, s, v);

    return 0;
}