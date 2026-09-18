#include <stdio.h>

double find_slope(double x1, double y1, double x2, double y2) {

    if(x1 == x2) {
        printf("Error: Can't find slope of a vertical line.\n");
        return 0;
    }

    return (y2 - y1) / (x2 - x1);
}


int main() {
    
    double x1 = 2, y1 = 2, x2 = 5, y2 = 7;
    double slope = find_slope(x1, y1, x2, y2);

    if(slope!=0) { printf("The slope of the line is %.2f\n", slope); }

    return 0;
}