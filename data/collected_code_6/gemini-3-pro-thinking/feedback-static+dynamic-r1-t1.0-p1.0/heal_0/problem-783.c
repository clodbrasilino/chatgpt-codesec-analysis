#include <stdio.h>
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

static uint8_t get_max(uint8_t a, uint8_t b, uint8_t c) {
    uint8_t max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

static uint8_t get_min(uint8_t a, uint8_t b, uint8_t c) {
    uint8_t min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}

HSV convert_rgb_to_hsv(RGB rgb) {
    HSV hsv = {0.0, 0.0, 0.0};
    
    uint8_t max_val = get_max(rgb.r, rgb.g, rgb.b);
    uint8_t min_val = get_min(rgb.r, rgb.g, rgb.b);
    uint8_t delta = max_val - min_val;

    hsv.v = max_val / 255.0;

    if (max_val == 0) {
        hsv.s = 0.0;
        hsv.h = 0.0;
        return hsv;
    }

    hsv.s = (double)delta / max_val;

    if (delta == 0) {
        hsv.h = 0.0;
        return hsv;
    }

    if (max_val == rgb.r) {
        hsv.h = 60.0 * (((double)rgb.g - rgb.b) / delta);
        if (rgb.g < rgb.b) {
            hsv.h += 360.0;
        }
    } else if (max_val == rgb.g) {
        hsv.h = 60.0 * (((double)rgb.b - rgb.r) / delta + 2.0);
    } else {
        hsv.h = 60.0 * (((double)rgb.r - rgb.g) / delta + 4.0);
    }

    return hsv;
}

int main(void) {
    RGB rgb = {255, 128, 0};
    HSV hsv = convert_rgb_to_hsv(rgb);

    printf("H: %.2f, S: %.2f, V: %.2f\n", hsv.h, hsv.s, hsv.v);

    return 0;
}