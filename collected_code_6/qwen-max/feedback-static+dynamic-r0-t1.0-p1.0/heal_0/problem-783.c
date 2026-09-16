#include <stdio.h>

void rgb_to_hsv(int r, int g, int b, float *h, float *s, float *v) {
    float rf = r / 255.0;
    float gf = g / 255.0;
    float bf = b / 255.0;

    float max_val = fmaxf(fmaxf(rf, gf), bf);
    float min_val = fminf(fminf(rf, gf), bf);
    float delta = max_val - min_val;

    *v = max_val;

    if (delta == 0) {
        *h = 0;
        *s = 0;
        return;
    }

    *s = delta / max_val;

    if (rf == max_val) {
        *h = (gf - bf) / delta + (gf < bf ? 6 : 0);
    } else if (gf == max_val) {
        *h = (bf - rf) / delta + 2;
    } else {
        *h = (rf - gf) / delta + 4;
    }

    *h /= 6;
}

int main() {
    int r = 255, g = 0, b = 0;
    float h, s, v;

    rgb_to_hsv(r, g, b, &h, &s, &v);

    printf("HSV: %f, %f, %f\n", h, s, v);

    return 0;
}