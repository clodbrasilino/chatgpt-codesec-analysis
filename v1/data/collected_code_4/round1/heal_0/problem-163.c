#include <math.h>
#include <stdio.h>

double findArea(double side, int total_sides){
    double area;
    double apothem = side / 2.0 / tan(3.14159265 / total_sides);
    area = 0.5 * total_sides * side * apothem;
    return area;
}

int main() {
    double side;
    int total_sides; 

    printf("Enter the length of a side and the number of sides of the regular polygon: \n");
    scanf("%lf %d", &side, &total_sides);

    if(side <= 0.0 || total_sides < 3) {
        printf("Entered values are not proper for a polygon.\n");
        return 0;
    }

    double area = findArea(side, total_sides);
    printf("The area of the regular polygon is %.2lf.\n", area);

    return 0;
}