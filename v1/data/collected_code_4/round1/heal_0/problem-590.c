#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Rectangle;

typedef struct {
    double r;
    double theta;
} Polar;

Rectangle convert_Polar_To_Rect(Polar inPolar) {
    Rectangle outRect;
    
    outRect.x = inPolar.r * cos(inPolar.theta);
    outRect.y = inPolar.r * sin(inPolar.theta);

    return outRect;
}

int main() {  
    Polar inPolar = {5, M_PI/6};  

    Rectangle outRect = convert_Polar_To_Rect(inPolar);  

    printf("In Rectangle format: x = %.2f, y = %.2f\n", outRect.x, outRect.y);  

    return 0;  
}