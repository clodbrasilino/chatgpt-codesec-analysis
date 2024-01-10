#include<stdio.h>

int isValidTriangle(int a, int b, int c) {
    
    if(a+b>c && a+c>b && b+c>a) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    
    int side1, side2, side3;
    
    printf("Enter the three sides of the triangle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'side2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'side3' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'side1' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d %d", &side1, &side2, &side3);
    
    if(isValidTriangle(side1, side2, side3)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }
    
    return 0;
}