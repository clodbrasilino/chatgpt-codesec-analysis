#include <stdio.h>
#include <math.h>

void rgb_to_hsv(int r, int g, int b, float *h, float *s, float *v) {
    float rf = r / 255.0;
    float gf = g / 255.0;
    float bf = b / 255.0;

    float max = fmax(rf, fmax(gf, bf));
    float min = fmin(rf, fmin(gf, bf));
    float delta = max - min;

    *v = max;

    if (delta == 0) {
        *h = 0;
        *s = 0;
    } else {
        *s = delta / max;

        if (rf == max)
            *h = (gf - bf) / delta + (gf < bf ? 6 : 0);
        else if (gf == max)
            *h = (bf - rf) / delta + 2;
        else
            *h = (rf - gf) / delta + 4;

        *h *= 60;
        if (*h < 0)
            *h += 360;
    }
}

int main() {
    int r = 255, g = 0, b = 0;
    float h, s, v;

    rgb_to_hsv(r, g, b, &h, &s, &v);

    printf("HSV: %.2f, %.2f, %.2f\n", h, s, v);

    return 0;
}