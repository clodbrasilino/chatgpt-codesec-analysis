#include <stdio.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct {
    double h;
    double s;
    double v;
} HSV;

HSV rgb_to_hsv(RGB color);

HSV rgb_to_hsv(RGB color) {
    HSV result = {0.0, 0.0, 0.0};
    
    double r = (double)color.r / 255.0;
    double g = (double)color.g / 255.0;
    double b = (double)color.b / 255.0;

    double cmax = r;
    if (g > cmax) {
        cmax = g;
    }
    if (b > cmax) {
        cmax = b;
    }

    double cmin = r;
    if (g < cmin) {
        cmin = g;
    }
    if (b < cmin) {
        cmin = b;
    }

    double diff = cmax - cmin;

    if (diff == 0.0) {
        result.h = 0.0;
    } else if (cmax == r) {
        result.h = 60.0 * ((g - b) / diff);
    } else if (cmax == g) {
        result.h = 60.0 * ((b - r) / diff) + 120.0;
    } else if (cmax == b) {
        result.h = 60.0 * ((r - g) / diff) + 240.0;
    }

    if (result.h < 0.0) {
        result.h += 360.0;
    }

    if (cmax == 0.0) {
        result.s = 0.0;
    } else {
        result.s = (diff / cmax) * 100.0;
    }

    result.v = cmax * 100.0;

    return result;
}

int main(void) {
    RGB color = {128, 64, 200};
    HSV result = rgb_to_hsv(color);
    
    printf("%.2f %.2f %.2f\n", result.h, result.s, result.v);
    
    return 0;
}