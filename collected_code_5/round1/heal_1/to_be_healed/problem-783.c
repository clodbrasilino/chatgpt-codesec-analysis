#include <stdio.h>
#include <stdlib.h>

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

HSV rgb2hsv(RGB in);

int main() {
    RGB inputRGB;
    HSV outputHSV;

    printf("Enter RGB values (between 0.0 - 1.0)\n");
    scanf("%f", &inputRGB.r);
    scanf("%f", &inputRGB.g);
    scanf("%f", &inputRGB.b);

    outputHSV = rgb2hsv(inputRGB);

    printf("HSV Values: H = %f, S = %f, V = %f\n", outputHSV.h, outputHSV.s, outputHSV.v);
    
    return 0;
}

HSV rgb2hsv(RGB in)
{
    HSV         out;
    float       min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;
    delta = max - min;
    if (delta < 0.00001f)
    {
        out.s = 0;
        out.h = 0;
        return out;
    }
    if( max > 0.0 ) {
        out.s = (delta / max);
    } else {
        out.s = 0.0f;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'NAN'
         */
        out.h = NAN;
        return out;
    }
    if( in.r >= max )
        out.h = ( in.g - in.b ) / delta;
    else
    if( in.g >= max )
        out.h = 2.0f + ( in.b - in.r ) / delta;
    else
        out.h = 4.0f + ( in.r - in.g ) / delta;

    out.h *= 60.0f;

    if( out.h < 0.0f )
        out.h += 360.0f;

    return out;
}