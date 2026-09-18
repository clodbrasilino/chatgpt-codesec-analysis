#include<stdio.h>

float trianglePerimeter(float side1, float side2, float side3){
    if(side1 <= 0 || side2 <= 0 || side3 <= 0){
        return -1;
    }

    if(side1+side2<=side3 || side1+side3<=side2 || side2+side3<=side1){
        return -1;
    }

    return side1 + side2 + side3;
}

int main(){
    float side1,side2,side3;
    float perimeter;

    printf("Enter the sides of triangle: ");
    scanf("%f %f %f",&side1,&side2,&side3);

    perimeter=trianglePerimeter(side1, side2, side3);
    if(perimeter==-1){
        printf("Invalid sides for a triangle\n");
    }
    else{
        printf("Perimeter of triangle is %.2f\n",perimeter);
    }
    return 0;
}