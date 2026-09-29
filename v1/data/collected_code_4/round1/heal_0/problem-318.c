#include <stdio.h>

double findMaxVol(int sumOfSides){
    double side = sumOfSides / 3.0;
    return side * side * side;
}

int main(){
    int sumOfSides;
    
    printf("Enter the sum of sides of the cuboid\n");    
    if(scanf("%d", &sumOfSides) != 1){
        printf("Invalid input\n");
        return 1;
    }
    
    if(sumOfSides <= 0){
        printf("The sum of sides must be positive\n");
        return 1;
    }
    
    double volume = findMaxVol(sumOfSides);
    
    printf("The maximum volume of the cuboid is %.2lf\n", volume);

    return 0;
}