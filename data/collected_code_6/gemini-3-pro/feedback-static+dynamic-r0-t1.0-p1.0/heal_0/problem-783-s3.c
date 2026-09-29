#include <stdio.h>
#include <math.h>
#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

typedef struct {
    double h;
    double s;
    double v;
} HSV;

HSV rgb_to_hsv(RGB rgb);

HSV rgb_to_hsv(RGB rgb) {
    HSV hsv = {0.0, 0.0, 0.0};
    
    double r = rgb.r / 255.0;
    double g = rgb.g / 255.0;
    double b = rgb.b / 255.0;

    double max = fmax(r, fmax(g, b));
    double min = fmin(r, fmin(g, b));
    double delta = max - min;

    hsv.v = max;

    if (max > 0.0) {
        hsv.s = delta / max;
    } else {
        hsv.s = 0.0;
        hsv.h = 0.0;
        return hsv;
    }

    if (delta <= 0.0) {
        hsv.h = 0.0;
    } else {
        if (max == r) {
            hsv.h = 60.0 * fmod(((g - b) / delta), 6.0);
        } else if (max == g) {
            hsv.h = 60.0 * (((b - r) / delta) + 2.0);
        } else if (max == b) {
            hsv.h = 60.0 * (((r - g) / delta) + 4.0);
        }
        
        if (hsv.h < 0.0) {
            hsv.h += 360.0;
        }
    }

    return hsv;
}

int main(void) {
    RGB rgb_colors[] = {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 255, 255},
        {0, 0, 0},
        {128, 128, 128},
        {255, 128, 0}
    };
    
    size_t num_colors = sizeof(rgb_colors) / sizeof(rgb_colors[0]);

    for (size_t i = 0; i < num_colors; ++i) {
        HSV hsv = rgb_to_hsv(rgb_colors[i]);
        printf("RGB(%3u, %3u, %3u) -> HSV(%6.2f, %4.2f, %4.2f)\n", 
               rgb_colors[i].r, rgb_colors[i].g, rgb_colors[i].b, 
               hsv.h, hsv.s, hsv.v);
    }

    return 0;
}