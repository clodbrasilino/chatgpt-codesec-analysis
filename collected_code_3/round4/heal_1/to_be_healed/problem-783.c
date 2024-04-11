#include <stdio.h>

typedef struct {
    double r;       
    double g;       
    double b;       
} rgb;

typedef struct {
    double h;       
    double s;       
    double v;       
} hsv;

hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                               
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; 
        return out;
    }
    if( max > 0.0 ) { 
        out.s = (delta / max);                  
    } else {
        out.s = 0.0;
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'NAN' undeclared (first use in this function)
         */
        out.h = NAN; 
        return out;
    }
    if( in.r >= max )                          
        out.h = ( in.g - in.b ) / delta;        
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  

    out.h *= 60.0;                              

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}

int main() {
    rgb in;
    hsv out;

    in.r = 0.6;
    in.g = 0.7;
    in.b = 0.8;

    out = rgb2hsv(in);

    printf("HSV: %f, %f, %f\n", out.h, out.s, out.v);

    return 0;
}