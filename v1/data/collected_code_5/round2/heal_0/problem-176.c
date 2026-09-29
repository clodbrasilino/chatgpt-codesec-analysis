#include<stdio.h>

float trianglePerimeter(float a, float b, float c) {
    if(a <= 0 || b <= 0 || c <= 0) {
        printf("Invalid input. Side lengths must be positive.\n");
        return 1;
    }
    if(a + b <= c || b + c <= a || c + a <= b) {
        printf("Invalid input. The sum of the lengths of any two sides must be greater than the length of the third side.\n");
        return 1;
    }
    float perimeter = a + b + c;
    return perimeter;
}


int main() {
    float a = 3.0, b = 4.0, c = 5.0;

    float perim = trianglePerimeter(a, b, c);
    
    if(perim != 1){
        printf("Perimeter of the triangle is: %.2f\n", perim);
    }
    
    return 0;
}