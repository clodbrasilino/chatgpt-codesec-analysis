#include <stdio.h>
#include <stdlib.h>

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

static double max3(double a, double b, double c)
{
    double m = a;
    if (b > m) {
        m = b;
    }
    if (c > m) {
        m = c;
    }
    return m;
}

static double min3(double a, double b, double c)
{
    double m = a;
    if (b < m) {
        m = b;
    }
    if (c < m) {
        m = c;
    }
    return m;
}

static HsvColor rgb_to_hsv(RgbColor rgb)
{
    HsvColor hsv;
    double r = (double)rgb.r / 255.0;
    double g = (double)rgb.g / 255.0;
    double b = (double)rgb.b / 255.0;
    double cmax = max3(r, g, b);
    double cmin = min3(r, g, b);
    double delta = cmax - cmin;

    hsv.v = cmax;

    if (delta <= 0.0) {
        hsv.h = 0.0;
        hsv.s = (cmax > 0.0) ? (delta / cmax) : 0.0;
        return hsv;
    }

    if (cmax > 0.0) {
        hsv.s = delta / cmax;
    } else {
        hsv.s = 0.0;
        hsv.h = 0.0;
        return hsv;
    }

    if (cmax == r) {
        hsv.h = 60.0 * ((g - b) / delta);
    } else if (cmax == g) {
        hsv.h = 60.0 * (((b - r) / delta) + 2.0);
    } else {
        hsv.h = 60.0 * (((r - g) / delta) + 4.0);
    }

    if (hsv.h < 0.0) {
        hsv.h += 360.0;
    }

    return hsv;
}

int main(void)
{
    RgbColor rgb;
    HsvColor hsv;
    int r;
    int g;
    int b;
    int result;

    printf("Enter RGB values (0-255) separated by spaces: ");

    result = scanf("%d %d %d", &r, &g, &b);
    if (result != 3) {
        fprintf(stderr, "Error: invalid input format\n");
        return EXIT_FAILURE;
    }

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: values must be in range 0-255\n");
        return EXIT_FAILURE;
    }

    rgb.r = (unsigned char)r;
    rgb.g = (unsigned char)g;
    rgb.b = (unsigned char)b;

    hsv = rgb_to_hsv(rgb);

    if (printf("H: %.2f degrees\nS: %.2f%%\nV: %.2f%%\n",
               hsv.h, hsv.s * 100.0, hsv.v * 100.0) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}