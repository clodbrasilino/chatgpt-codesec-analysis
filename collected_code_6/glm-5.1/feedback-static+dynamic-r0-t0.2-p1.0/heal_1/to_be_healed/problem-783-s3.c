#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'fmod'
  */

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Rgb;

typedef struct {
    double h;
    double s;
    double v;
} Hsv;

Hsv rgb_to_hsv(Rgb rgb) {
    Hsv hsv;
    double r = rgb.r / 255.0;
    double g = rgb.g / 255.0;
    double b = rgb.b / 255.0;

    double max = r;
    if (g > max) max = g;
    if (b > max) max = b;

    double min = r;
    if (g < min) min = g;
    if (b < min) min = b;

    hsv.v = max;

    double delta = max - min;

    if (max == 0.0) {
        hsv.s = 0.0;
        hsv.h = 0.0;
        return hsv;
    }

    hsv.s = delta / max;

    if (delta == 0.0) {
        hsv.h = 0.0;
    } else if (max == r) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'fmod' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'fmod'
         *  implicit declaration of function 'fmod' [-Wimplicit-function-declaration]
         */
        hsv.h = 60.0 * (fmod(((g - b) / delta), 6.0));
    } else if (max == g) {
        hsv.h = 60.0 * (((b - r) / delta) + 2.0);
    } else {
        hsv.h = 60.0 * (((r - g) / delta) + 4.0);
    }

    if (hsv.h < 0.0) {
        hsv.h += 360.0;
    }

    return hsv;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <R> <G> <B>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val;

    val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 255) {
        fprintf(stderr, "Invalid R value\n");
        return EXIT_FAILURE;
    }
    unsigned char r = (unsigned char)val;

    val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 255) {
        fprintf(stderr, "Invalid G value\n");
        return EXIT_FAILURE;
    }
    unsigned char g = (unsigned char)val;

    val = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 255) {
        fprintf(stderr, "Invalid B value\n");
        return EXIT_FAILURE;
    }
    unsigned char b = (unsigned char)val;

    Rgb rgb = {r, g, b};
    Hsv hsv = rgb_to_hsv(rgb);

    printf("H: %.2f, S: %.2f, V: %.2f\n", hsv.h, hsv.s, hsv.v);

    return EXIT_SUCCESS;
}