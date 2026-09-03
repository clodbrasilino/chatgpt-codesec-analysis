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
    
    max = rgb.r;
    if (rgb.g > max) max = rgb.g;
    if (rgb.b > max) max = rgb.b;
    
    min = rgb.r;
    if (rgb.g < min) min = rgb.g;
    if (rgb.b < min) min = rgb.b;
    
    hsv.v = max;
    delta = max - min;
    
    if (max > 0.0f) {
        hsv.s = delta / max;
    } else {
        hsv.s = 0.0f;
        hsv.h = 0.0f;
        return hsv;
    }
    
    if (delta > 0.0f) {
        if (max == rgb.r) {
            hsv.h = 60.0f * (fmodf(((rgb.g - rgb.b) / delta), 6.0f));
        } else if (max == rgb.g) {
            hsv.h = 60.0f * (((rgb.b - rgb.r) / delta) + 2.0f);
        } else {
            hsv.h = 60.0f * (((rgb.r - rgb.g) / delta) + 4.0f);
        }
        
        if (hsv.h < 0.0f) {
            hsv.h += 360.0f;
        }
    } else {
        hsv.h = 0.0f;
    }
    
    return hsv;
}

int main(void) {
    RGB rgb;
    HSV hsv;
    
    rgb.r = 0.5f;
    rgb.g = 0.2f;
    rgb.b = 0.8f;
    
    hsv = rgb_to_hsv(rgb);
    
    printf("RGB: %.2f, %.2f, %.2f\n", rgb.r, rgb.g, rgb.b);
    printf("HSV: %.2f, %.2f, %.2f\n", hsv.h, hsv.s, hsv.v);
    
    return 0;
}