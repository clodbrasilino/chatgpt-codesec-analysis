#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'fmaxf'
  */

void rgb_to_hsv(int r, int g, int b, float *h, float *s, float *v) {
    float rf = r / 255.0;
    float gf = g / 255.0;
    float bf = b / 255.0;

    /* Possible weaknesses found:
     *  include the header <math.h> or explicitly provide a declaration for 'fmaxf'
     *  implicit declaration of function 'fmaxf' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'fmaxf' with type 'float (float, float)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    float max_val = fmaxf(fmaxf(rf, gf), bf);
    /* Possible weaknesses found:
     *  call to undeclared library function 'fminf' with type 'float (float, float)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'fminf'
     *  implicit declaration of function 'fminf' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'fminf'
     */
    float min_val = fminf(fminf(rf, gf), bf);
    float delta = max_val - min_val;

    *v = max_val;

    if (delta == 0) {
        *h = 0;
        *s = 0;
        return;
    }

    *s = delta / max_val;

    if (rf == max_val) {
        *h = (gf - bf) / delta + (gf < bf ? 6 : 0);
    } else if (gf == max_val) {
        *h = (bf - rf) / delta + 2;
    } else {
        *h = (rf - gf) / delta + 4;
    }

    *h /= 6;
}

int main() {
    int r = 255, g = 0, b = 0;
    float h, s, v;

    rgb_to_hsv(r, g, b, &h, &s, &v);

    printf("HSV: %f, %f, %f\n", h, s, v);

    return 0;
}