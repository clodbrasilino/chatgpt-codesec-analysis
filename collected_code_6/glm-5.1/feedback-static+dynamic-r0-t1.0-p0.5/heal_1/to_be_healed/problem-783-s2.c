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
    double max = r > g ? (r > b ? r : b) : (g > b ? g : b);
    double min = r < g ? (r < b ? r : b) : (g < b ? g : b);
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
    } else if (max == r) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'fmod' [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'fmod'
         *  call to undeclared library function 'fmod' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        hsv.h = 60.0 * fmod((g - b) / delta, 6.0);
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

    char *endptr_r;
    char *endptr_g;
    char *endptr_b;
    long val_r = strtol(argv[1], &endptr_r, 10);
    long val_g = strtol(argv[2], &endptr_g, 10);
    long val_b = strtol(argv[3], &endptr_b, 10);

    if (*endptr_r != '\0' || *endptr_g != '\0' || *endptr_b != '\0' ||
        val_r < 0 || val_r > 255 || val_g < 0 || val_g > 255 || val_b < 0 || val_b > 255) {
        fprintf(stderr, "Error: R, G, B must be integers between 0 and 255\n");
        return EXIT_FAILURE;
    }

    Rgb rgb;
    rgb.r = (unsigned char)val_r;
    rgb.g = (unsigned char)val_g;
    rgb.b = (unsigned char)val_b;

    Hsv hsv = rgb_to_hsv(rgb);

    printf("H: %.2f, S: %.2f, V: %.2f\n", hsv.h, hsv.s, hsv.v);

    return EXIT_SUCCESS;
}