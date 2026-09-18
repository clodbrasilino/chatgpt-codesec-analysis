#include<stdio.h>
#include<math.h>

double findAreaOfSector(double radius, double angle) {
    if(radius < 0 || angle < 0 || angle > 360) {
        printf("Invalid input \n");
        return -1;
    }
    
    double sectorArea = 0.5 * radius * radius * (angle * M_PI / 180);
    return sectorArea;
}

int main() {
    double radius, angle;

    printf("Enter radius: ");
    scanf("%lf", &radius);

    printf("Enter angle in degree: ");
    scanf("%lf", &angle);

    double area = findAreaOfSector(radius, angle);
    if(area != -1)
        printf("Area of the sector is: %.2lf\n", area);
    
    return 0;
}