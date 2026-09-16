#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double h;
    double s;
    double v;
} HsvColor;

HsvColor rgb_to_hsv(unsigned char r, unsigned char g, unsigned char b) {
    HsvColor hsv;
    double rd = (double)r / 255.0;
    double gd = (double)g / 255.0;
    double bd = (double)b / 255.0;

    double max = rd;
    if (gd > max) max = gd;
    if (bd > max) max = bd;

    double min = rd;
    if (gd < min) min = gd;
    if (bd < min) min = bd;

    double delta = max - min;

    hsv.v = max;

    if (max == 0.0) {
        hsv.s = 0.0;
        hsv.h = 0.0;
        return hsv;
    }

    hsv.s = delta / max;

    if (delta == 0.0) {
        hsv.h = 0.0;
        return hsv;
    }

    if (max == rd) {
        hsv.h = (gd - bd) / delta;
    } else if (max == gd) {
        hsv.h = 2.0 + (bd - rd) / delta;
    } else {
        hsv.h = 4.0 + (rd - gd) / delta;
    }

    hsv.h *= 60.0;

    if (hsv.h < 0.0) {
        hsv.h += 360.0;
    }

    return hsv;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <R> <G> <B>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long rl = strtol(argv[1], NULL, 10);
    long gl = strtol(argv[2], NULL, 10);
    long bl = strtol(argv[3], NULL, 10);

    if (rl < 0 || rl > 255 || gl < 0 || gl > 255 || bl < 0 || bl > 255) {
        fprintf(stderr, "Error: RGB values must be in range 0-255\n");
        return EXIT_FAILURE;
    }

    unsigned char r = (unsigned char)rl;
    unsigned char g = (unsigned char)gl;
    unsigned char b = (unsigned char)bl;

    HsvColor hsv = rgb_to_hsv(r, g, b);

    printf("RGB(%d, %d, %d) -> HSV(%.2f, %.4f, %.4f)\n", r, g, b, hsv.h, hsv.s, hsv.v);

    return EXIT_SUCCESS;
}