#include <stdio.h>
#include <math.h>

double area_pentagon(int side, int apothem){
    if (side < 0 || apothem < 0) {
        printf("Invalid Side or Apothem Value.\n");
        return -1;
    }
    double area = 0.5 * 5 * side * apothem;
    return area;
}

int main() {
    int side, apothem;
    
    printf("Enter the length of side: ");
    scanf("%d", &side);

    printf("Enter the length of apothem: ");
    scanf("%d", &apothem);

    double area = area_pentagon(side, apothem);

    if(area != -1){
        printf("\nThe area of the pentagon is: %.2lf", area);
    }
    else{
        printf("Could not calculate the area of the pentagon");
    }

    return 0;
}