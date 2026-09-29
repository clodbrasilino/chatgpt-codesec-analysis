#include <stdio.h>

double calculateParallelogramArea(double base, double height){
    if(base <= 0 || height <= 0) {
        printf("Error: Base and height must be greater than zero.\n");
        return -1;
    }
    return base * height;
}

int main() {
    double base, height, area;

    printf("Enter base and height of the parallelogram: ");
    scanf("%lf%lf", &base, &height);

    area = calculateParallelogramArea(base, height);

    if(area != -1) {
        printf("Area of parallelogram is: %.2lf\n", area);
    }
    
    return 0;
}