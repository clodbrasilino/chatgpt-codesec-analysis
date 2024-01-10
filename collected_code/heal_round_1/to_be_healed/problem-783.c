/* Possible weaknesses found:
 *  include '<math.h>' or provide a declaration of 'fmax'
 */
void RGBtoHSV(int r, int g, int b, double* h, double* s, double* v) {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'fmax' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'fmax' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'fmax'
     */
    double max = fmax(fmax(r, g), b);
    /* Possible weaknesses found:
     *  include '<math.h>' or provide a declaration of 'fmin'
     *  implicit declaration of function 'fmin' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'fmin' [-Wbuiltin-declaration-mismatch]
     */
    double min = fmin(fmin(r, g), b);
    double delta = max - min;
    
    if (delta == 0) {
        *h = 0;
    }
    else if (max == r) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'fmod' [-Wimplicit-function-declaration]
         *  include '<math.h>' or provide a declaration of 'fmod'
         *  incompatible implicit declaration of built-in function 'fmod' [-Wbuiltin-declaration-mismatch]
         */
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