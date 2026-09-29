#include<stdio.h>
#include<math.h>

double find_third_side(double side1, double side2){
    if(side1 > 0 && side2 > 0){
        double square_side1 = pow(side1, 2);
        double square_side2 = pow(side2, 2);
        
        double square_side3 = square_side1 + square_side2;
        double side3 = sqrt(square_side3);
        
        return side3;
    }else{
        printf("\nNote: Both input sides must be positive.");
        return -1;
    }
}

int main(){
    double side1, side2;

    printf("Enter the first side: ");
    scanf("%lf", &side1);

    printf("Enter the second side: ");
    scanf("%lf", &side2);

    double side3 = find_third_side(side1, side2);
    if(side3 != -1)
        printf("\nThe third side of the right angled triangle is: %.2lf\n", side3);

    return 0;
}