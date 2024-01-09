void RGBtoHSV(int r, int g, int b, double* h, double* s, double* v) {
    double max = fmax(fmax(r, g), b);
    double min = fmin(fmin(r, g), b);
    double delta = max - min;
    
    if (delta == 0) {
        *h = 0;
    }
    else if (max == r) {
        *h = 60 * fmod(((g - b) / delta), 6);
    }
    else if (max == g) {
        *h = 60 * (((b - r) / delta) + 2);
    }
    else if (max == b) {
        *h = 60 * (((r - g) / delta) + 4);
    }
    
    if (max == 0) {
        *s = 0;
    }
    else {
        *s = (delta / max) * 100;
    }
    
    *v = (max / 255) * 100;
}