#include <stdio.h>
#include <math.h>


double find_volume_of_cone(double radius, double height) {
    if(radius < 0 || height < 0) {
        printf("Radius and height must be positive.\n");
        return -1.0;
    }
    
    double volume = (M_PI * pow(radius, 2) * height) / 3.0;
    return volume;
}

int main(void) {
    double radius;
    double height;
    printf("Enter radius: ");
    scanf("%lf", &radius);

    printf("Enter height: ");
    scanf("%lf", &height);

    double volume = find_volume_of_cone(radius, height);

    if(volume != -1.0) {
        printf("Volume of the cone: %.2lf\n", volume);
    }

    return 0;
}