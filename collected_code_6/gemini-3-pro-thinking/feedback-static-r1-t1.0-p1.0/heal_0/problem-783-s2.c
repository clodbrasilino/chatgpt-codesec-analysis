#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double r;
    double g;
    double b;
} RGB;

typedef struct {
    double h;
    double s;
    double v;
} HSV;

typedef enum {
    COLOR_SUCCESS = 0,
    COLOR_ERROR_NULL_POINTER = 1,
    COLOR_ERROR_OUT_OF_RANGE = 2
} ColorStatus;

ColorStatus convert_rgb_to_hsv(const RGB *rgb, HSV *hsv);

ColorStatus convert_rgb_to_hsv(const RGB *rgb, HSV *hsv) {
    double max_val;
    double min_val;
    double diff;

    if (rgb == NULL || hsv == NULL) {
        return COLOR_ERROR_NULL_POINTER;
    }

    if (rgb->r < 0.0 || rgb->r > 1.0 ||
        rgb->g < 0.0 || rgb->g > 1.0 ||
        rgb->b < 0.0 || rgb->b > 1.0) {
        return COLOR_ERROR_OUT_OF_RANGE;
    }

    max_val = rgb->r;
    if (rgb->g > max_val) {
        max_val = rgb->g;
    }
    if (rgb->b > max_val) {
        max_val = rgb->b;
    }

    min_val = rgb->r;
    if (rgb->g < min_val) {
        min_val = rgb->g;
    }
    if (rgb->b < min_val) {
        min_val = rgb->b;
    }

    diff = max_val - min_val;
    hsv->v = max_val;

    if (max_val <= 0.0) {
        hsv->s = 0.0;
    } else {
        hsv->s = diff / max_val;
    }

    if (diff <= 0.0) {
        hsv->h = 0.0;
    } else {
        if (max_val == rgb->r) {
            hsv->h = 60.0 * ((rgb->g - rgb->b) / diff);
        } else if (max_val == rgb->g) {
            hsv->h = 60.0 * ((rgb->b - rgb->r) / diff) + 120.0;
        } else {
            hsv->h = 60.0 * ((rgb->r - rgb->g) / diff) + 240.0;
        }

        if (hsv->h < 0.0) {
            hsv->h += 360.0;
        }
    }

    return COLOR_SUCCESS;
}

int main(void) {
    RGB rgb = {0.2, 0.4, 0.6};
    HSV hsv = {0.0, 0.0, 0.0};
    ColorStatus status;

    status = convert_rgb_to_hsv(&rgb, &hsv);

    if (status != COLOR_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (printf("%.2f %.2f %.2f\n", hsv.h, hsv.s, hsv.v) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}