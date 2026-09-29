#include <stdio.h>

struct RGB {
    double r; 
    double g; 
    double b; 
};

struct HSV {
    double h; 
    double s; 
    double v; 
};

struct HSV rgb2hsv(struct RGB in) {
    struct HSV         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max; 

    delta = max - min;

    if (delta < 0.00001) {
        out.s = 0;
        out.h = 0; 
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max); // s
    } else {
        out.s = 0.0;
        out.h = 0; 
        return out;
    }
    if( in.r >= max ) {
        out.h = ( in.g - in.b ) / delta; 
    } else if( in.g >= max ) {
        out.h = 2.0 + ( in.b - in.r ) / delta;
    } else {
        out.h = 4.0 + ( in.r - in.g ) / delta;
    }

    out.h *= 60.0; 

    if( out.h < 0.0 ) {
        out.h += 360.0;
    }

    return out;
}

int main() {
    struct RGB input;
    input.r = 23;
    input.g = 147;
    input.b = 209;

    struct HSV output = rgb2hsv(input);

    printf("H: %f, S: %f, V: %f\n", output.h, output.s, output.v);

    return 0;
}