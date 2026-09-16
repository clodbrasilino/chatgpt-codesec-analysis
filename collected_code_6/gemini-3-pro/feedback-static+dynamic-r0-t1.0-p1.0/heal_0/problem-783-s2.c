#include <stdio.h>
#include <math.h>

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

HSV convert_rgb_to_hsv(RGB color) {
    HSV result = {0.0, 0.0, 0.0};
    
    double r = color.r / 255.0;
    double g = color.g / 255.0;
    double b = color.b / 255.0;

    double max_val = fmax(r, fmax(g, b));
    double min_val = fmin(r, fmin(g, b));
    double delta = max_val - min_val;

    result.v = max_val;

    if (max_val > 0.0) {
        result.s = delta / max_val;
    } else {
        result.s = 0.0;
        result.h = 0.0;
        return result;
    }

    if (delta <= 0.0) {
        result.h = 0.0;
    } else {
        if (max_val == r) {
            result.h = 60.0 * ((g - b) / delta);
        } else if (max_val == g) {
            result.h = 60.0 * (((b - r) / delta) + 2.0);
        } else if (max_val == b) {
            result.h = 60.0 * (((r - g) / delta) + 4.0);
        }

        if (result.h < 0.0) {
            result.h += 360.0;
        }
    }

    return result;
}

int main(void) {
    RGB num_color = {129, 88, 47};
    HSV converted_color = convert_rgb_to_hsv(num_color);

    printf("%f %f %f\n", converted_color.h, converted_color.s, converted_color.v);

    return 0;
}