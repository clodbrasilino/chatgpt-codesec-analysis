#include <stdio.h>
#include <math.h>

typedef struct {
    float r;
    float g;
    float b;
} RGB;

typedef struct {
    float h;
    float s;
    float v;
} HSV;

HSV rgb_to_hsv(RGB rgb) {
    HSV hsv;
    float max, min, delta;
    
    max = fmaxf(rgb.r, fmaxf(rgb.g, rgb.b));
    min = fminf(rgb.r, fminf(rgb.g, rgb.b));
    delta = max - min;
    
    hsv.v = max;
    
    if (max == 0.0f) {
        hsv.s = 0.0f;
    } else {
        hsv.s = delta / max;
    }
    
    if (delta == 0.0f) {
        hsv.h = 0.0f;
    } else if (max == rgb.r) {
        hsv.h = 60.0f * fmodf(((rgb.g - rgb.b) / delta), 6.0f);
    } else if (max == rgb.g) {
        hsv.h = 60.0f * (((rgb.b - rgb.r) / delta) + 2.0f);
    } else {
        hsv.h = 60.0f * (((rgb.r - rgb.g) / delta) + 4.0f);
    }
    
    if (hsv.h < 0.0f) {
        hsv.h += 360.0f;
    }
    
    return hsv;
}

int main(void) {
    RGB rgb;
    HSV hsv;
    
    rgb.r = 255.0f;
    rgb.g = 0.0f;
    rgb.b = 0.0f;
    
    rgb.r /= 255.0f;
    rgb.g /= 255.0f;
    rgb.b /= 255.0f;
    
    hsv = rgb_to_hsv(rgb);
    
    printf("RGB: %.2f, %.2f, %.2f\n", rgb.r, rgb.g, rgb.b);
    printf("HSV: %.2f, %.2f, %.2f\n", hsv.h, hsv.s, hsv.v);
    
    return 0;
}