#include <stdio.h>
#include <math.h>

void rgb_to_hsv(float r, float g, float b, float *h, float *s, float *v) {
    float max = fmax(fmax(r, g), b);
    float min = fmin(fmin(r, g), b);
    float delta = max - min;

    *v = max;
    if (delta == 0) {
        *s = 0;
        *h = 0;
    } else {
        *s = delta / max;
        float h_prime = 0;
        if (max == r)
            h_prime = (g - b) / delta + (g < b ? 6 : 0);
        else if (max == g)
            h_prime = (b - r) / delta + 2;
        else if (max == b)
            h_prime = (r - g) / delta + 4;
        *h = h_prime * 60.0f;
        if (*h < 0)
            *h += 360.0f;
    }
}

int main() {
    float r = 0.5, g = 0.5, b = 1.0;
    float h, s, v;

    rgb_to_hsv(r, g, b, &h, &s, &v);
    printf("H: %f, S: %f, V: %f\n", h, s, v);

    return 0;
}