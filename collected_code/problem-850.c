#include<stdio.h>

int checkTriangle(int angle1, int angle2, int angle3){
    if(angle1 + angle2 + angle3 == 180){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){

    int angle1, angle2, angle3;

    // Input angles from user
    printf("Enter three angles of the triangle: ");
    scanf("%d %d %d", &angle1, &angle2, &angle3);

    // Check if triangle is possible
    if(checkTriangle(angle1, angle2, angle3)){
        printf("Triangle is possible.");
    }
    else{
        printf("Triangle is not possible.");
    }
    
    return 0;
}